#include <iostream>
#include <string>
#include "Rational.h"

using namespace std;

Rational::Rational(const int &numerator, const int &denominator)
   :  mNumerator(numerator), mDenominator(denominator)
{
   Normalize();
}

Rational::Rational()
   :  mNumerator(0), mDenominator(1)
{
   Normalize();
}

Rational::Rational(const Rational &copyThis)
{
   mNumerator = copyThis.mNumerator;
   mDenominator = copyThis.mDenominator;
}

const int Rational::GetNumerator() const {
   return mNumerator;
}

const int Rational::GetDenominator() const {
   return mDenominator;
}

void Rational::SetNumerator(int numerator) {
   mNumerator = numerator;
   Normalize();
}

void Rational::SetDenominator(int denominator) {
   mDenominator = denominator;
   Normalize();
}

bool Rational::Equals(const Rational &other) const {
   if (mNumerator == other.mNumerator && mDenominator == other.mDenominator) {
      return true;
   }
   else {
      return false;
   }
}

Rational Rational::Add(const Rational &other) const {
   int numerator = mDenominator * other.mNumerator
      + other.mDenominator * mNumerator;
   int denominator = mDenominator * other.mDenominator;
   return Rational(numerator, denominator);
}

const string Rational::ToString() const {
   string rationalNumber;
   if (mDenominator == 0 || mDenominator == 1) {
      return rationalNumber = to_string(mNumerator);
   }
   else {
      return rationalNumber = to_string(mNumerator) + "/"
         + to_string(mDenominator);
   }
}

void Rational::Normalize() {
   if (mDenominator < 0 && (mNumerator > 0 || mNumerator < 0)) {
      mNumerator *= -1;
      mDenominator *= -1;
   }
   int scalar = gcd(mNumerator, mDenominator);
   if (scalar < 0) {
      scalar *= -1;
   }
   mNumerator /= scalar;
   mDenominator /= scalar;
}

const int Rational::gcd(int numberOne, int numberTwo) {
   while (numberTwo != 0) {
      int remainder = numberOne % numberTwo;
      numberOne = numberTwo;
      numberTwo = remainder;
   }
   return numberOne;
}

ostream &operator<<(std::ostream &lhs, const Rational &rhs) {
   lhs << rhs.ToString() << endl;
   return lhs;
}

Rational& Rational::operator=(const Rational &rhs) {
   mNumerator = rhs.mNumerator;
   mDenominator = rhs.mDenominator;
   return *this;
}

const Rational operator+(const Rational &lhs, const Rational &rhs) {
   return lhs.Add(rhs);
}

const Rational operator-(const Rational &rhs) {
   int numerator = rhs.mNumerator * -1;
   int denominator = rhs.mDenominator;
   return Rational(numerator, denominator);
}

const Rational operator-(const Rational &lhs, const Rational &rhs) {
   int numerator = rhs.mDenominator * lhs.mNumerator
         - lhs.mDenominator * rhs.mNumerator;
   int denominator = lhs.mDenominator * rhs.mDenominator;
   return Rational(numerator, denominator);
}

const Rational operator*(const Rational &lhs, const Rational &rhs) {
   int numerator = lhs.mNumerator * rhs.mNumerator;
   int denominator = lhs.mDenominator * rhs.mDenominator;
   return Rational(numerator, denominator);
}

const Rational operator/(const Rational &lhs, const Rational &rhs) {
   int numerator = lhs.mNumerator * rhs.mDenominator;
   int denominator = lhs.mDenominator * rhs.mNumerator;
   return Rational(numerator, denominator);
}

const bool operator==(const Rational &lhs, const Rational &rhs) {
   return lhs.Equals(rhs);
}

const bool operator!=(const Rational &lhs, const Rational &rhs) {
   return !(lhs==rhs);
}

const bool operator<(const Rational &lhs, const Rational &rhs) {
   int first = lhs.mNumerator / lhs.mDenominator;
   int second = rhs.mNumerator / rhs.mDenominator;
   return first < second;
}

const bool operator>(const Rational &lhs, const Rational &rhs) {
   int first = lhs.mNumerator / lhs.mDenominator;
   int second = rhs.mNumerator / rhs.mDenominator;
   return first > second;
}

const bool operator<=(const Rational &lhs, const Rational &rhs) {
   int first = lhs.mNumerator / lhs.mDenominator;
   int second = rhs.mNumerator / rhs.mDenominator;
   return first <= second;
}

const bool operator>=(const Rational &lhs, const Rational &rhs) {
   int first = lhs.mNumerator / lhs.mDenominator;
   int second = rhs.mNumerator / rhs.mDenominator;
   return first >= second;
}
