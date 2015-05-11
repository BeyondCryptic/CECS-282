#include "ConnectFourBoard.h"
#include "ConnectFourMove.h"

using namespace std;

ConnectFourBoard::ConnectFourBoard()
: GameBoard()
{
   for (int i = 0; i < BOARD_SIZE_CR; i++) {
      for (int j = 0; j < BOARD_SIZE_CC; j++) {
         mBoard[i][j] = 0;
      }
   }
}

void ConnectFourBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {
   for (int j = 0; j < BOARD_SIZE_CC; j++) {
      for (int i = 0; i < BOARD_SIZE_CR; i++) {
         if (mBoard[i][j] == 0) { // Found empty spot
            ConnectFourMove *aMove =
               dynamic_cast<ConnectFourMove*>(CreateMove());
            if (aMove == nullptr) {
               throw ConnectFourException("Tried to apply a non-ConnectFourMove.");
            }
            aMove->mCol = LETTER_A + j;
            list->push_back(aMove);
            break;
         }
      }
   }
}

void ConnectFourBoard::ApplyMove(GameMove *move) {
   ConnectFourMove *m = dynamic_cast<ConnectFourMove*>(move);
   if (m == nullptr) {
      throw ConnectFourException("Tried to apply a non-ConnectFourMove.");
   }
   mHistory.push_back(m);
   int realCol = m->mCol - LETTER_A; // Gets back the REAL column value.
   int prevRow = 0;
   for (int i = 0; i < BOARD_SIZE_CR; i++) {
      if (mBoard[i][realCol] == 0) {
         prevRow = i;
      }
      if (mBoard[i][realCol] != 0) {
         mBoard[prevRow][realCol] = GetNextPlayer();
         m->mRealRow = prevRow;
         m->mRealCol = realCol;
      }
      else if (mBoard[i][realCol] == 0 && i == BOARD_SIZE_CR - 1) {
         mBoard[i][realCol] = GetNextPlayer();
         m->mRealRow = i;
         m->mRealCol = realCol;
      }
   }
   mValue = GetNextPlayer();
   if (mHistory.size() == MAX_PLAYS_C) {
      if (!IsFourInARow()) {
         mValue = 0;
      }
   }
   mNextPlayer = GetNextPlayer() == Y ? R : Y;
}

void ConnectFourBoard::UndoLastMove() {
   ConnectFourMove* move = dynamic_cast<ConnectFourMove*>(GetMoveHistory()->back());
   if (move == nullptr) {
      throw ConnectFourException("Tried to apply a non-ConnectFourMove.");
   }
   int row = move->mRealRow;
   int col = move->mRealCol;
   mValue = GetNextPlayer();
   mBoard[row][col] = EMPTY;
   mHistory.pop_back();
   delete move;
   mNextPlayer = GetNextPlayer() == Y ? R : Y;
}

bool ConnectFourBoard::IsFinished() const {
   // Check from (0, 0) - Vertical
   for (int i = 0; i < VERTICAL_DEPTH; i++) {
      for (int j = 0; j < BOARD_SIZE_CC; j++) {
         int y = 0, r = 0;
         for (int k = i; k < i + FOUR_IN_A_ROW; k++) {
            if (mBoard[k][j] == 1) {
               y++;
            }
            if (mBoard[k][j] == -1) {
               r++;
            }
            if (y == Y_COUNT || r == R_COUNT) {
               return true;
            }
         }
      }
   }
   // Check from (0, 0) - Horizontal
   for (int i = 0; i < BOARD_SIZE_CR; i++) {
      for (int j = 0; j < HORIZONTAL_DEPTH; j++) {
         int y = 0, r = 0;
         for (int k = j; k < j + FOUR_IN_A_ROW; k++) {
            if (mBoard[i][k] == 1) {
               y++;
            }
            if (mBoard[i][k] == -1) {
               r++;
            }
            if (y == Y_COUNT || r == R_COUNT) {
               return true;
            }
         }
      }
   }
   // Check from (0, 0) - Diagonals
   int shiftRow = 0;
   int shiftCol = 1;
   for (int i = 0; i < MAX_DIAGONAL_DEPTH; i++) {
      int realDepth = MAX_DIAGONAL_DEPTH - i;
      for (int j = 0; j < realDepth; j++) {
         // cout << "Depth " << j + 1 << endl;
         int y = 0, r = 0, yS = 0, rS = 0;
         int startingRow = i + j;
         int startingCol = j;
         int aCol = startingCol;
         for (int aRow = startingRow; aRow < FOUR_IN_A_ROW + startingRow; aRow++) {
            // cout << "Regular Row: (" << aRow << ", " << aCol << ")" << endl;
            // cout << "Shifted Row: (" << aRow + shiftRow << ", " << aCol + shiftCol << ")" << endl;
            if (mBoard[aRow][aCol] == 1) {
               y++;
            }
            if (mBoard[aRow][aCol] == -1) {
               r++;
            }
            if (mBoard[aRow + shiftRow][aCol + shiftCol] == 1) {
               y++;
            }
            if (mBoard[aRow + shiftRow][aCol + shiftCol] == -1) {
               r++;
            }
            if (y == Y_COUNT || r == R_COUNT
               || yS == Y_COUNT || rS == R_COUNT) {
               return true;
            }
            aCol++;
         }
      }
      shiftRow--;
      shiftCol++;
   }
   // Check from (0, 6) - Anti-Diagonals
   int shiftRowA = 0;
   int shiftColA = -1;
   for (int i = 0; i < MAX_DIAGONAL_DEPTH; i++) {
      int realDepth = MAX_DIAGONAL_DEPTH - i;
      for (int j = 0; j < realDepth; j++) {
         // cout << "Depth " << j + 1 << endl;
         int y = 0, r = 0, yS = 0, rS = 0;
         int startingRow = i + j;
         int startingCol = 6-j;
         int aCol = startingCol;
         for (int aRow = startingRow; aRow < FOUR_IN_A_ROW + startingRow; aRow++) {
            // cout << "Regular Row: (" << aRow << ", " << aCol << ")" << endl;
            // cout << "Shifted Row: (" << aRow + shiftRowA << ", " << aCol + shiftColA << ")" << endl;
            if (mBoard[aRow][aCol] == 1) {
               y++;
            }
            if (mBoard[aRow][aCol] == -1) {
               r++;
            }
            if (y == Y_COUNT || r == R_COUNT) {
               return true;
            }
            if (mBoard[aRow + shiftRowA][aCol + shiftColA] == 1) {
               yS++;
            }
            if (mBoard[aRow + shiftRowA][aCol + shiftColA] == -1) {
               rS++;
            }
            if (y == Y_COUNT || r == R_COUNT
               || yS == Y_COUNT || rS == R_COUNT) {
               return true;
            }
            aCol--;
         }
      }
      shiftRowA--;
      shiftColA--;
   }
   // Checks for tie.
   if (mHistory.size() == MAX_PLAYS_C) {
      return true;
   }
   return false;
}

bool ConnectFourBoard::IsFourInARow() {
   // Check from (0, 0) - Vertical
   for (int i = 0; i < VERTICAL_DEPTH; i++) {
      for (int j = 0; j < BOARD_SIZE_CC; j++) {
         int y = 0, r = 0;
         for (int k = i; k < i + FOUR_IN_A_ROW; k++) {
            if (mBoard[k][j] == 1) {
               y++;
            }
            if (mBoard[k][j] == -1) {
               r++;
            }
            if (y == Y_COUNT || r == R_COUNT) {
               return true;
            }
         }
      }
   }
   // Check from (0, 0) - Horizontal
   for (int i = 0; i < BOARD_SIZE_CR; i++) {
      for (int j = 0; j < HORIZONTAL_DEPTH; j++) {
         int y = 0, r = 0;
         for (int k = j; k < j + FOUR_IN_A_ROW; k++) {
            if (mBoard[i][k] == 1) {
               y++;
            }
            if (mBoard[i][k] == -1) {
               r++;
            }
            if (y == Y_COUNT || r == R_COUNT) {
               return true;
            }
         }
      }
   }
   // Check from (0, 0) - Diagonals
   int shiftRow = 0;
   int shiftCol = 1;
   for (int i = 0; i < MAX_DIAGONAL_DEPTH; i++) {
      int realDepth = MAX_DIAGONAL_DEPTH - i;
      for (int j = 0; j < realDepth; j++) {
         // cout << "Depth " << j + 1 << endl;
         int y = 0, r = 0;
         int startingRow = i + j;
         int startingCol = j;
         int aCol = startingCol;
         for (int aRow = startingRow; aRow < FOUR_IN_A_ROW + startingRow; aRow++) {
            // cout << "Regular Row: (" << aRow << ", " << aCol << ")" << endl;
            // cout << "Shifted Row: (" << aRow + shiftRow << ", " << aCol + shiftCol << ")" << endl;
            if (mBoard[aRow][aCol] == 1) {
               y++;
            }
            if (mBoard[aRow][aCol] == -1) {
               r++;
            }
            if (y == Y_COUNT || r == R_COUNT) {
               return true;
            }
            aCol++;
         }
      }
      shiftRow--;
      shiftCol++;
   }
   // Check from (0, 6) - Anti-Diagonals
   int shiftRowA = 0;
   int shiftColA = -1;
   for (int i = 0; i < MAX_DIAGONAL_DEPTH; i++) {
      int realDepth = MAX_DIAGONAL_DEPTH - i;
      for (int j = 0; j < realDepth; j++) {
         // cout << "Depth " << j + 1 << endl;
         int y = 0, r = 0;
         int startingRow = i + j;
         int startingCol = 6-j;
         int aCol = startingCol;
         for (int aRow = startingRow; aRow < FOUR_IN_A_ROW + startingRow; aRow++) {
            // cout << "Regular Row: (" << aRow << ", " << aCol << ")" << endl;
            // cout << "Shifted Row: (" << aRow + shiftRowA << ", " << aCol + shiftColA << ")" << endl;
            if (mBoard[aRow][aCol] == 1) {
               y++;
            }
            if (mBoard[aRow][aCol] == -1) {
               r++;
            }
            if (y == Y_COUNT || r == R_COUNT) {
               return true;
            }
            aCol--;
         }
      }
      shiftRowA--;
      shiftColA--;
   }
   return false;
}
