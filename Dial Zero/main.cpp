#include <iostream>
#include <string>
#include "Rational.h"

using namespace std;

int main(int argc, char* arcv[]) {
   Rational r1(4, 3);
   Rational r2(5, 12);
   cout << "Testing Copy Constructor" << endl;
   cout << "Value of R1: " << r1.ToString() << endl;
   cout << "Copying Value of R1 to R3: " << endl;
   Rational r3(r1);
   cout << "R3's Value: " << r3.ToString() << endl;
   cout << "Assigning using overloaded operator: " << endl;
   cout << "Value of R3 before assignment: " << r3.ToString() << endl;
   r3 = r2;
   cout << "Value of R3 after assignment: " << r3.ToString() << endl;
   cout << "The above was also a test of the overloading of "
      "the \"<<\" operator!" << endl;
   cout << "Adding using overloaded operator: " << endl;
   cout << r1.ToString() << " + " << r2.ToString() << " = "
      << r1+r2 << endl;
   cout << "Negating using overloaded operator: " << endl;
   cout << "Negation of " << r1.ToString() << " = "
      << -r1 << endl;
   cout << "Subtracting using overloaded operator: " << endl;
   cout << r1.ToString() << " - " << r2.ToString() << " = "
      << r1-r2 << endl;
   cout << "Multiplying using overloaded operator: " << endl;
   cout << r1.ToString() << " * " << r2.ToString() << " = "
      << r1*r2 << endl;
   cout << "Dividing using overloaded operator: " << endl;
   cout << r1.ToString() << " * " << r2.ToString() << " = "
      << r1/r2 << endl;
   cout << "Testing equality using overloaded operator: " << endl;
   cout << "R1's Value: " << r1.ToString() << endl;
   cout << "R2's Value: " << r2.ToString() << endl;
   cout << "R3's Value: " << r3.ToString() << endl;
   cout << "Is R1 equal to R3?" << endl;
   int testEquality2 = r1==r3;
   string result2 = (testEquality2 != 0) ? "Yes!" : "No.";
   cout << result2 << endl;
   cout << "Is R2 equal to R3?" << endl;
   int testEquality3 = r2==r3;
   string result3 = (testEquality3 != 0) ? "Yes!" : "No.";
   cout << result3 << endl;
   cout << "Is R1 NOT equal to R3?" << endl;
   int testEquality4 = r1!=r3;
   string result4 = (testEquality4 != 0) ? "Yes!" : "No.";
   cout << result4 << endl;
   cout << "Is R2 NOT equal to R3?" << endl;
   int testEquality5 = r2!=r3;
   string result5 = (testEquality5 != 0) ? "Yes!" : "No.";
   cout << result5 << endl;
   cout << "Is R1 < R2?" << endl;
   int testEquality6 = r1<r2;
   string result6 = (testEquality6 != 0) ? "Yes!" : "No.";
   cout << result6 << endl;
   cout << "Is R1 > R2?" << endl;
   int testEquality7 = r1>r2;
   string result7 = (testEquality7 != 0) ? "Yes!" : "No.";
   cout << result7 << endl;
   cout << "Is R1 <= R2?" << endl;
   int testEquality8 = r1<=r2;
   string result8 = (testEquality8 != 0) ? "Yes!" : "No.";
   cout << result8 << endl;
   cout << "Is R1 >= R2?" << endl;
   int testEquality9 = r1>=r2;
   string result9 = (testEquality9 != 0) ? "Yes!" : "No.";
   cout << result9 << endl;
}
