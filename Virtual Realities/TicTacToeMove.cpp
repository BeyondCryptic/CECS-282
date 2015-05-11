#include <iostream>
#include <string>
#include <sstream>
#include "TicTacToeMove.h"
#include "GameExceptions.h"

using namespace std;

int TicTacToeMove::mOnHeap = 0;
const int MAX_SIZE = 3;

TicTacToeMove::TicTacToeMove()
   : mRow(-1), mCol(-1) // Not a pass...
{
}

TicTacToeMove::TicTacToeMove(int row, int col)
   : mRow(row), mCol(col)
{
}

GameMove& TicTacToeMove::operator=(const std::string &move) {
   istringstream s(move);
   char junk;
   s >> junk >> mRow >> junk >> mCol >> junk;
   if (mRow >= MAX_SIZE || mRow < 0 || mCol >= MAX_SIZE || mCol < 0) {
      throw TicTacToeException("out of bounds");
   }
   return *this;
}

bool TicTacToeMove::Equals(const GameMove &other) const {
   const TicTacToeMove &casted = dynamic_cast<const TicTacToeMove&>(other);
   if (this->mRow == casted.mRow && this->mCol == casted.mCol) {
      return true;
   }
   return false;
}

TicTacToeMove::operator std::string() const {
   ostringstream s;
   s << "(" << mRow << ", " << mCol << ")";
   return s.str();
}
