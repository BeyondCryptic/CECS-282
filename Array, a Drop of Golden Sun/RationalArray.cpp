#include <iostream>
#include <string>
#include <stdexcept>
#include "Rational.h"
#include "RationalArray.h"

using namespace std;

RationalArray::RationalArray(int size)
   :  mSize(size), mArray(new Rational[size])
{
}

RationalArray::~RationalArray() {
   delete[] mArray;
   mArray = nullptr;
}

RationalArray::RationalArray(const RationalArray &other)
   :  mSize(other.Size()), mArray(new Rational[other.Size()])
{
   for (int i = 0; i < other.Size(); i++) {
      mArray[i] = other[i];
   }
}

RationalArray& RationalArray::operator=(const RationalArray& rhs) {
   if (Size() == rhs.Size()) {
      for (int i = 0; i < rhs.Size(); i++) {
        mArray[i] = rhs[i];
      }
   }
   else {
      delete[] mArray;
      mArray = nullptr;
      mSize = rhs.mSize;
      mArray = new Rational[mSize];
      for (int i = 0; i < rhs.Size(); i++) {
         mArray[i] = rhs[i];
      }
   }
   return *this;
}

Rational& RationalArray::operator[](int rhs) const {
   if (rhs > Size()-1) {
      throw out_of_range(": out of bounds!");
   }
   return mArray[rhs];
}
