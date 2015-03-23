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
   Rational(const Rational &copyThis);
   const int GetNumerator() const;
   const int GetDenominator() const;
   void SetNumerator(int numerator);
   void SetDenominator(int denominator);
   bool Equals(const Rational &other) const;
   Rational Add(const Rational &other) const;
   const std::string ToString() const;
   friend std::ostream &operator<<(std::ostream &lhs, const Rational &rhs);
   Rational &operator=(const Rational &rhs);
   friend const Rational operator+(const Rational &lhs, const Rational &rhs);
   friend const Rational operator-(const Rational &rhs);
   friend const Rational operator-(const Rational &lhs, const Rational &rhs);
   friend const Rational operator*(const Rational &lhs, const Rational &rhs);
   friend const Rational operator/(const Rational &lhs, const Rational &rhs);
   friend const bool operator==(const Rational &lhs, const Rational &rhs);
   friend const bool operator!=(const Rational &lhs, const Rational &rhs);
   friend const bool operator<(const Rational &lhs, const Rational &rhs);
   friend const bool operator>(const Rational &lhs, const Rational &rhs);
   friend const bool operator<=(const Rational &lhs, const Rational &rhs);
   friend const bool operator>=(const Rational &lhs, const Rational &rhs);
};

#endif
