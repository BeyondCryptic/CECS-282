#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include "HitTheTarget.h"

using namespace std;

const int MAX_DISTANCE = 1000, SPEED_PER_KG = 30, HALF_CIRCLE = 180;
const double GRAVITY = 9.8, PI = 3.141592653589793238463;
int seed;
double dist, angle, gunpowder, velocity, velocityX, velocityY, timeTraveled,
   distTraveled;
bool hit = false;

int main(int argc, char* argv[]) {

   getSeed();

   default_random_engine engine(seed);
   uniform_real_distribution<double> distr(1, MAX_DISTANCE);

   dist = distr(engine); //222.77;

   cout << "The target is " << setprecision(2) << fixed << dist <<
      "m away." << endl;

   getAngle();

   angle = degreesToRadians(angle);

   getGunpowder();

   while(!hit) {
      if ((distTraveled > dist + 1) || (distTraveled < dist - 1)) {
         cout << "You were " << abs(dist-distTraveled) << "m short." << endl;
      }
      else {
         cout << "It's a hit!" << endl;
         hit = true;
      }
      getAngle();
      angle = degreesToRadians(angle);
      getGunpowder();
   }
}

double degreesToRadians(double angle) {
   return (angle*PI)/HALF_CIRCLE;
}

void getSeed() {
   cout << "Please enter a positive integer seed value: " << endl;
   cin >> seed;
   while (seed <= 0) {
      cout << "Please enter a positive integer seed value: " << endl;
      cin >> seed;
   }
}

void getAngle() {
   cout << "Please enter an angle between 0 and 90 degrees: " << endl;
   cin >> angle;

   while (angle < 0 || angle > 90) {
      cout << "Please enter an angle between 0 and 90 degrees: " << endl;
      cin >> angle;
   }
}

void getGunpowder() {
   cout << "Please enter an amount of gunpowder in kilograms: " << endl;
   cin >> gunpowder;

   velocity = gunpowder * SPEED_PER_KG;

   velocityX = velocity * cos(angle);
   velocityY = velocity * sin(angle);

   timeTraveled = 2 * velocityY / GRAVITY;
   distTraveled = velocityX * timeTraveled;
}
