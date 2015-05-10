#include "TicTacToeView.h"

using namespace std;

void TicTacToeView::PrintBoard(std::ostream &s) const {
   s << "\n- 0 1 2" << endl;
   for (int i = 0; i < BOARD_SIZE_T; i++) {
      s << i << " ";
      for (int j = 0; j < BOARD_SIZE_T; j++) {
         if (mTicTacToeBoard->mBoard[i][j] == 0) {
            cout << '.' << " ";
         }
         else if (mTicTacToeBoard->mBoard[i][j] == 1) {
            cout << 'X' << " ";
         }
         else if (mTicTacToeBoard->mBoard[i][j] == -1) {
            cout << 'O' << " ";
         }
      }
      s << endl;
   }
   s << endl;
}
