#include "OthelloView.h"

using namespace std;

void OthelloView::PrintBoard(std::ostream &s) const {
   s << "\n- 0 1 2 3 4 5 6 7" << endl;
   for (int i = 0; i < BOARD_SIZE; i++) {
      s << i << " ";
      for (int j = 0; j < BOARD_SIZE; j++) {
         if (mOthelloBoard->mBoard[i][j] == 0) {
            cout << '.' << " ";
         }
         else if (mOthelloBoard->mBoard[i][j] == 1) {
            cout << 'B' << " ";
         }
         else if (mOthelloBoard->mBoard[i][j] == -1) {
            cout << 'W' << " ";
         }
      }
      s << endl;
   }
   s << endl;
}

ostream& operator<< (ostream &lhs, const OthelloView &rhs) {
   rhs.PrintBoard(lhs);
   return lhs;
}
