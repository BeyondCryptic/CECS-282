#include <iostream>
#include <string>
#include "Rational.h"

using namespace std;

int main(int argc, char* arcv[]) {
   Rational r1;
   const Rational r2(5, 12);
   cout << "R2's Value: " << r2.ToString() << endl;
   r1.SetNumerator(48);
   r1.SetDenominator(36);
   cout << "R1's Numerator: " << r1.GetNumerator() << endl;
   cout << "R1's Denominator: " << r1.GetDenominator() << endl;
   int testEquality = r1.Equals(r2);
   string result = (testEquality != 0) ? "Yes!" : "No.";
   cout << "Are the two numbers equal? " << result << endl;
   cout << r1.ToString() << " + " << r2.ToString() << " = "
      << r1.Add(r2) << endl;
}
