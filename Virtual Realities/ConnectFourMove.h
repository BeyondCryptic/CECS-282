#ifndef __CONNECTFOURMOVE_H
#define __CONNECTFOURMOVE_H
#include "GameMove.h"
#include <string>
#include <iostream>
/*
An ConnectFourMove encapsulates a single potential move on an ConnectFourBoard. It
is represented internally by a row and column, both 0-based.
*/
class ConnectFourMove : public GameMove {
private:
   // ConnectFourBoard is a friend so it can access mRow and mCol.
   friend class ConnectFourBoard;

   int mRealRow, mRealCol;
   char mCol;

   // KEEP THESE CONSTRUCTORS PRIVATE.
   // Default constructor
   ConnectFourMove();
   /*
   2-parameter constructor: initializes this move with the given
   row and column.
   */
   ConnectFourMove(char col);

public:
   static int mOnHeap;

   static void* operator new(std::size_t sz){
      mOnHeap++;
      std::cout << "operator new: " << mOnHeap << " ConnectFourMoves on the heap" << std::endl;
      return ::operator new(sz);
   }

      static void operator delete(void* ptr, std::size_t sz) {
      mOnHeap--;
      std::cout << "operator delete: " << mOnHeap << " ConnectFourMoves on the heap" << std::endl;
      ::operator delete(ptr);
   }

   /*
   This assignment operator takes a string representation of an ConnectFourmove
   and uses it to initialize the move. The string is in the format
   (r, c); OR is the string "pass". [The user will not enter (-1,-1) to pass
   anymore.]
   */
   virtual GameMove& operator=(const std::string &);

   /*
   Compares two ConnectFourMove objects for equality.
   */
   virtual bool Equals(const GameMove &other) const;

   // Converts the ConnectFourMove into a string representation, one that could be
   // used correctly with operator=(string). Returns "pass" if move is a pass.
   virtual operator std::string() const;
};

#endif
