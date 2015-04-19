#include "OthelloBoard.h"
#include "OthelloMove.h"

using namespace std;

OthelloBoard::OthelloBoard()
   : mNextPlayer(BLACK), mValue(0), mPassCount(0)
{
   for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
         mBoard[i][j] = 0;
      }
   }
   mBoard[3][3] = WHITE; // -1
   mBoard[3][4] = BLACK; // 1
   mBoard[4][3] = BLACK; // 1
   mBoard[4][4] = WHITE; // -1
}

void OthelloBoard::GetPossibleMoves(std::vector<OthelloMove *> *list) const {

}

void OthelloBoard::ApplyMove(OthelloMove *move) {
   // Nxt = Next, Nw = New, c = count...
   if (move->mCol != -1 && move->mRow != -1) {
      int bValue = 2, wValue = 2;
      mBoard[move->mRow][move->mCol] = GetNextPlayer();
      mHistory.push_back(move);
      mValue = GetNextPlayer() == 1 ? ++bValue - wValue : bValue - ++wValue;
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
                           xNxt : false, yNxt > 0 ? yNxt : false));
                     }
                     mBoard[xPrev][yPrev] = GetNextPlayer();
                     mValue = GetNextPlayer() == 1 ?
                        ++bValue - --wValue : --bValue - ++wValue;
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
   OthelloMove* move = CreateMove();
   move = GetMoveHistory()->back();
   int row = move->mRow;
   int col = move->mCol;
   for (OthelloMove::FlipSet f : move->mFlips) {
      for (int i = f.switched; i > 0; i++) {
         int rowDelta = f.rowDelta == 0 ? -1 * i : 1 * i;
         int colDelta = f.colDelta == 0 ? -1 * i : 1 * i;
         mBoard[row + rowDelta][col + colDelta] = GetNextPlayer();
      }
      move->mFlips.pop_back();
   }
   move->mFlips.clear();
   mBoard[row][col] = EMPTY;
   mHistory.pop_back();
   delete move;
}
