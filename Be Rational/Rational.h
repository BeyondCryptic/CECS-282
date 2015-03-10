#include <iostream>
#include <string>
#ifndef __RATIONAL_H
#define __RATIONAL_H

class Rational {
private:
   int mNumerator;
   int mDenominator;
   void Normalize();
   const int gcd(int numberOne, int numberTwo);
public:
   Rational(const int &numerator, const int &denominator);
   Rational();
   const int GetNumerator() const;
   const int GetDenominator() const;
   void SetNumerator(int numerator);
   void SetDenominator(int denominator);
   const bool Equals(const Rational &other);
   Rational Add(const Rational &other);
   const std::string ToString() const;
   friend std::ostream &operator<<(std::ostream &lhs, const Rational &rhs);
};

#endif
