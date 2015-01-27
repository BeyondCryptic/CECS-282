#include <iostream>
#include <random>

using namespace std;

int main(int argc, char* argv[]) {
   const int MAX_DOOR_CHOICE = 3;
   const int MAX_PRIZE_CHOICE = 5;

   random_device rd;
   default_random_engine engine(rd());
   uniform_int_distribution<int> distr(1, MAX_DOOR_CHOICE);

   int winningDoor = distr(engine);

   // cout << "Winning door: " << winningDoor << endl;

   int userChoice;

   cout << "Please choose a door, 1 to 3: " << endl;
   cin >> userChoice;

   while (userChoice != 1 && userChoice != 2 && userChoice != 3) {
      cout << "Please enter a valid choice!" << endl;
      cin >> userChoice;
   }

   cout << "We will now reveal a door." << endl;

   int doorShown = distr(engine);

   while (doorShown == winningDoor || doorShown == userChoice) {
      doorShown = distr(engine);
   }

   cout << "Door " << doorShown << " was revealed. There was a goat behind it. Do you want to switch doors, yes (y) or no (n)?" << endl;

   char switchDoors;

   bool win = false;

   cin >> switchDoors;

   if (switchDoors != 'y' && switchDoors != 'n') {
      cout << "Please enter a valid choice!" << endl;
      cin >> switchDoors;
   }

   if (switchDoors == 'y') {
      int doorSwitchedTo = distr(engine);
      while (doorSwitchedTo == userChoice || doorSwitchedTo == doorShown) {
         doorSwitchedTo = distr(engine);
      }
      cout << "Door " << doorSwitchedTo << " was opened." << endl;
      if (winningDoor == doorSwitchedTo) {
         cout << "Congratulations,  you've won!" << endl;
         win = true;
      }
      else {
         cout << "Sorry, you lost." << endl;
      }
   }
   else {
      if (userChoice == winningDoor) {
         cout << "Congratulations,  you've won!" << endl;
         win = true;
      }
      else {
         cout << "Sorry, you lost." << endl;
      }
   }

   if (win) {
      int prize = distr(engine);
      uniform_int_distribution<int> distr(1, MAX_PRIZE_CHOICE);
      cout << "You've won prize number " << prize << " which is ";
      if (prize == 1) {
         cout << "a PS4." << endl;
      }
      if (prize == 2) {
         cout << "a laptop." << endl;
      }
      if (prize == 3) {
         cout << "an iPod." << endl;
      }
      if (prize == 4) {
         cout << "a piece of gum." << endl;
      }
      if (prize == 5) {
         cout << "nothing." << endl;
      }
   }

}
