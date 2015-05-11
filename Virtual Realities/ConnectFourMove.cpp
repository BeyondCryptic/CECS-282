#include <iostream>
#include <string>
#include <sstream>
#include "ConnectFourMove.h"
#include "GameExceptions.h"

using namespace std;

int ConnectFourMove::mOnHeap = 0;
const int MAX_SIZE_A = 65;
const int MAX_SIZE_G = 71;

ConnectFourMove::ConnectFourMove()
   : mRealRow(-1), mRealCol(-1), mCol(-1) // Not a pass...
{
}

ConnectFourMove::ConnectFourMove(char col)
   : mRealRow(-1), mRealCol(-1), mCol(col)
{
}

GameMove& ConnectFourMove::operator=(const std::string &move) {
   istringstream s(move.substr(0, 1));
   s >> mCol;
   if (mCol < MAX_SIZE_A || mCol > MAX_SIZE_G) {
      throw ConnectFourException("out of bounds (not a valid column)");
   }
   return *this;
}

bool ConnectFourMove::Equals(const GameMove &other) const {
   const ConnectFourMove &casted = dynamic_cast<const ConnectFourMove&>(other);
   if (this->mCol == casted.mCol) {
      return true;
   }
   return false;
}

ConnectFourMove::operator std::string() const {
   ostringstream s;
   s << mCol;
   return s.str();
}
