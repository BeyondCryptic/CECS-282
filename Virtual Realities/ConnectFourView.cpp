#include "ConnectFourView.h"

using namespace std;

void ConnectFourView::PrintBoard(std::ostream &s) const {
   s << "\nA B C D E F G" << endl;
   for (int i = 0; i < BOARD_SIZE_CR; i++) {
      for (int j = 0; j < BOARD_SIZE_CC; j++) {
         if (mConnectFourBoard->mBoard[i][j] == 0) {
            cout << '.' << " ";
         }
         else if (mConnectFourBoard->mBoard[i][j] == 1) {
            cout << 'Y' << " ";
         }
         else if (mConnectFourBoard->mBoard[i][j] == -1) {
            cout << 'R' << " ";
         }
      }
      s << endl;
   }
   s << endl;
}
