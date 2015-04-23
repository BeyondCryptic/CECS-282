#include "OthelloBoard.h"
#include "OthelloMove.h"

using namespace std;

OthelloBoard::OthelloBoard()
: mNextPlayer(BLACK), mValue(0), mPassCount(0)
{
   const int START = 3;
   for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
         mBoard[i][j] = 0;
      }
   }
   mBoard[START][START] = WHITE; // -1
   mBoard[START][START + 1] = BLACK; // 1
   mBoard[START + 1][START] = BLACK; // 1
   mBoard[START + 1][START + 1] = WHITE; // -1
}

void OthelloBoard::GetPossibleMoves(std::vector<OthelloMove *> *list) const {
   char otherPlayer = GetNextPlayer() == BLACK ? WHITE : BLACK;
   for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
         if (mBoard[i][j] == 0) { // Found empty spot, now check in all directions.
            bool added = false;
            for (int xNxt = -1; xNxt <= 1; xNxt++) {
               for (int yNxt = -1; yNxt <= 1; yNxt++) {
                  int xNw = i + xNxt, yNw = j + yNxt; // Next (first) spot in that direction.
                  while (InBounds(xNw, yNw) && mBoard[xNw][yNw] != 0) {
                     if (mBoard[xNw][yNw] == otherPlayer) {
                        while (mBoard[xNw][yNw] == otherPlayer) {
                           int xDNxt = xNw + xNxt, yDNxt = yNw + yNxt/*, duplicateFound = 0*/; // Next-next spot in that direction
                           if (InBounds(xDNxt, yDNxt) &&
                              mBoard[xDNxt][yDNxt] == GetNextPlayer()) { // Found friendly piece after walking!
                              if (!added) {
                                 OthelloMove *aMove = CreateMove();
                                 aMove->mRow = i;
                                 aMove->mCol = j;
                                 list->push_back(aMove);
                                 added = true;
                              }
                              break;
                              /* for (OthelloMove *moves : *list) {
                                 if (*aMove == *moves) {
                                    delete aMove;
                                    duplicateFound = true;
                                    break;
                                 }
                              }
                              if (!duplicateFound) {
                                 list->push_back(aMove);
                                 break;
                              } */
                           }
                           xNw += xNxt;
                           yNw += yNxt;
                        }
                     }
                     break;
                  }
               }
            }
         }
      }
   }
   if (list->empty()) {
      list->push_back(CreateMove());
   }
}

void OthelloBoard::ApplyMove(OthelloMove *move) {
   // Nxt = Next, Nw = New, c = count...
   mHistory.push_back(move);
   if (move->mRow != -1 && move->mCol != -1) {
      mPassCount = 0;
      mBoard[move->mRow][move->mCol] = GetNextPlayer();
      mValue = GetNextPlayer() == 1 ? mValue + 1: mValue - 1;
      for (int xNxt = -1; xNxt <= 1; xNxt++) {
         for (int yNxt = -1; yNxt <= 1; yNxt++) {
            if (xNxt != 0 || yNxt != 0) {
               int xNw = move->mRow + xNxt, yNw = move->mCol + yNxt, c = 0;
               while (InBounds(xNw, yNw) && mBoard[xNw][yNw] != 0) {
                  int xPrev = xNw - xNxt, yPrev = yNw - yNxt, flipped = 0;
                  if (mBoard[xNw][yNw] != GetNextPlayer()) {
                     c += 1;
                  }
                  while (mBoard[xNw][yNw] == GetNextPlayer() && c > 0) {
                     if (!flipped++) { // Cheap Hack... Curses, line limit!
                        move->AddFlipSet(OthelloMove::FlipSet(c, xNxt > 0 ?
                           xNxt : xNxt == 0 ? 2 : false, yNxt > 0 ?
                              yNxt : yNxt == 0 ? 2 : false));
                     }
                     mBoard[xPrev][yPrev] = GetNextPlayer();
                     mValue = GetNextPlayer() == 1 ? mValue + 1: mValue - 1;
                     xPrev -= xNxt;
                     yPrev -= yNxt;
                     c -= 1;
                  }
                  if (mBoard[xNw][yNw] == GetNextPlayer() && c == 0) {
                     break;
                  }
                  xNw += xNxt;
                  yNw += yNxt;
               }
               // xNw = move->mRow + xNxt; // Not needed...?
               // yNw = move->mCol + yNxt; // Not needed...?
            }
         }
      }
   }
   else {
      mPassCount++;
   }
   mNextPlayer = GetNextPlayer() == BLACK ? WHITE : BLACK;
}

void OthelloBoard::UndoLastMove() {
   OthelloMove* move = GetMoveHistory()->back();
   int row = move->mRow;
   int col = move->mCol;
   for (OthelloMove::FlipSet f : move->mFlips) {
      for (int i = f.switched; i > 0; i--) {
         int rowDelta = f.rowDelta == 0 ? -1 * i : f.rowDelta == 1 ? 1 * i : 0;
         int colDelta = f.colDelta == 0 ? -1 * i : f.colDelta == 1 ? 1 * i : 0;
         mValue = GetNextPlayer() == 1 ? mValue - 1: mValue + 1;
         mBoard[row + rowDelta][col + colDelta] = GetNextPlayer();
         // cout << row << ", " << col << endl;
         // cout << "Undo: " << rowDelta + row << ", " << colDelta + col << endl;
      }
      move->mFlips.pop_back();
   }
   move->mFlips.clear();
   mValue = GetNextPlayer() == 1 ? mValue - 1: mValue + 1;
   if (mPassCount == 1) {
      mPassCount--;
   }
   mBoard[row][col] = EMPTY;
   mHistory.pop_back();
   delete move;
   mNextPlayer = GetNextPlayer() == BLACK ? WHITE : BLACK;
}
