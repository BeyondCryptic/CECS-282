#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"

using namespace std;

TicTacToeBoard::TicTacToeBoard()
: GameBoard()
{
   for (int i = 0; i < BOARD_SIZE_T; i++) {
      for (int j = 0; j < BOARD_SIZE_T; j++) {
         mBoard[i][j] = 0;
      }
   }
}

void TicTacToeBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {
   for (int i = 0; i < BOARD_SIZE_T; i++) {
      for (int j = 0; j < BOARD_SIZE_T; j++) {
         if (mBoard[i][j] == 0) { // Found empty spot
            TicTacToeMove *aMove =
               dynamic_cast<TicTacToeMove*>(CreateMove());
            if (aMove == nullptr) {
               throw TicTacToeException("Tried to apply a non-TicTacToeMove.");
            }
            aMove->mRow = i;
            aMove->mCol = j;
            list->push_back(aMove);
         }
      }
   }
}

void TicTacToeBoard::ApplyMove(GameMove *move) {
   TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(move);
   if (m == nullptr) {
      throw TicTacToeException("Tried to apply a non-TicTacToeMove.");
   }
   mHistory.push_back(m);
   mBoard[m->mRow][m->mCol] = GetNextPlayer();
   mValue = GetNextPlayer();
   if (!IsThreeInARow()) {
      mValue = 0;
   }
   mNextPlayer = GetNextPlayer() == X ? O : X;
}

void TicTacToeBoard::UndoLastMove() {
   TicTacToeMove* move = dynamic_cast<TicTacToeMove*>(GetMoveHistory()->back());
   if (move == nullptr) {
      throw TicTacToeException("Tried to apply a non-TicTacToeMove.");
   }
   int row = move->mRow;
   int col = move->mCol;
   mValue = 0;
   mBoard[row][col] = EMPTY;
   mHistory.pop_back();
   delete move;
   mNextPlayer = GetNextPlayer() == X ? O : X;
}

bool TicTacToeBoard::IsFinished() const {
   if (IsThreeInARow()) {
      return true;
   }
   // Checks for tie.
   if (mHistory.size() == MAX_PLAYS_T) {
      return true;
   }
   return false;
}

bool TicTacToeBoard::IsThreeInARow() const {
   // Check from (0, 0) - Vertical
   for (int i = 0; i < BOARD_SIZE_T; i++) {
      int x = 0, o = 0;
      for (int j = 0; j < BOARD_SIZE_T; j++) {
         if (mBoard[i][j] == 0) {
            break;
         }
         if (mBoard[i][j] == 1) {
            x++;
         }
         if (mBoard[i][j] == -1) {
            o++;
         }
         if (x == X_COUNT || o == O_COUNT) {
            return true;
         }
      }
   }
   // Check from (0, 0) - Horizontal
   for (int i = 0; i < BOARD_SIZE_T; i++) {
      int x = 0, o = 0;
      for (int j = 0; j < BOARD_SIZE_T; j++) {
         if (mBoard[j][i] == 0) {
            break;
         }
         if (mBoard[j][i] == 1) {
            x++;
         }
         if (mBoard[j][i] == -1) {
            o++;
         }
         if (x == X_COUNT || o == O_COUNT) {
            return true;
         }
      }
   }
   // Check from (0, 0) - Diagonals
   int xD = 0, oD = 0;
   for (int i = 0; i < BOARD_SIZE_T; i++) {
      int j = i;
      if (mBoard[i][j] == 0) {
         break;
      }
      if (mBoard[i][j] == 1) {
         xD++;
      }
      if (mBoard[i][j] == -1) {
         oD++;
      }
      if (xD == X_COUNT || oD == O_COUNT) {
         return true;
      }
   }
   // Check from (0, 2) - Anti-Diagonals
   int xAD = 0, oAD = 0;
   for (int i = 0; i < BOARD_SIZE_T; i++) {
      int j = 2-i;
      if (mBoard[i][j] == 0) {
         break;
      }
      if (mBoard[i][j] == 1) {
         xAD++;
      }
      if (mBoard[i][j] == -1) {
         oAD++;
      }
      if (xAD == X_COUNT || oAD == O_COUNT) {
         return true;
      }
   }
   return false;
}
