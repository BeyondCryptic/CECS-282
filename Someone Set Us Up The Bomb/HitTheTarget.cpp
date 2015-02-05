#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include "HitTheTarget.h"

using namespace std;

const int MAX_DISTANCE = 1000, SPEED_PER_KG = 30, HALF_CIRCLE = 180;
const double GRAVITY = 9.8, PI = 3.141592653589793238463;

int main(int argc, char* argv[]) {

   int seed;
   double dist, angle, gunpowder, vel = 0, distTraveled;
   bool hit = false;

   int &aSeed = seed;
   getSeed(aSeed);

   default_random_engine engine(seed);
   uniform_real_distribution<double> distr(1, MAX_DISTANCE);

   dist = 222.77;

   cout << "The target is " << setprecision(2) << fixed << dist <<
      "m away." << endl;
   double &anAngle = angle;
   getAngle(anAngle);

   angle = degreesToRadians(angle);

   double &someGunpowder = gunpowder, &aDistance = distTraveled, &aVel = vel;
   getGunpowder(someGunpowder, aVel, anAngle, aDistance);

   while(!hit) {
      if ((distTraveled > dist + 1) || (distTraveled < dist - 1)) {
         cout << "You were " << abs(dist-distTraveled) << "m short." << endl;
      }
      else {
         cout << "It's a hit!" << endl;
         hit = true;
         return 0;
      }
      getAngle(anAngle);
      angle = degreesToRadians(angle);
      getGunpowder(someGunpowder, aVel, anAngle, aDistance);
   }
}

double degreesToRadians(double angle) {
   return (angle*PI)/HALF_CIRCLE;
}

void getSeed(int &seed) {
   cout << "Please enter a positive integer seed value: " << endl;
   cin >> seed;
   while (seed <= 0) {
      cout << "Please enter a positive integer seed value: " << endl;
      cin >> seed;
   }
}

void getAngle(double &angle) {
   cout << "Please enter an angle between 0 and 90 degrees: " << endl;
   cin >> angle;

   while (angle < 0 || angle > 90) {
      cout << "Please enter an angle between 0 and 90 degrees: " << endl;
      cin >> angle;
   }
}

void getGunpowder(double &gunpowder, double &vel, double &ang, double &distT) {
   cout << "Please enter an amount of gunpowder in kilograms: " << endl;
   cin >> gunpowder;

   vel = gunpowder * SPEED_PER_KG;

   distT = (vel * vel * sin(2 * ang))/GRAVITY;
}
