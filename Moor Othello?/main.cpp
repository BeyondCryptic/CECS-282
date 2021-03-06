#include "OthelloExceptions.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


int main(int argc, char* argv[]) {
   // Initialization
   OthelloBoard board; // the state of the game board
   OthelloView v(&board); // a View for outputting the board via operator<<
   string userInput; // a string to hold the user's command choice
   vector<OthelloMove *> possMoves; // a holder for possible moves

   //
   //   // Start with this DEBUGGING CODE to make sure your basic OthelloMove and
   //   // OthelloBoard classes work, then remove it when you are ready to work
   //   // on the real main.
   //   cout << "Initial board:" << endl;
   //   cout << v << endl;
   //   board.GetPossibleMoves(&possMoves);
   //   OthelloMove *m = board.CreateMove();
   //   *m = "(3, 2)";
   //   cout << "Applying the move " << (string)(*m) << endl;
   //   board.ApplyMove(m);
   //   cout << endl << v << endl; // should show a changed board.
   //   cout << board.GetValue() << endl;
   //
   //   m = board.CreateMove();
   //   *m = "(4, 2)";
   //   cout << "Applying the move " << (string)(*m) << endl;
   //   board.ApplyMove(m);
   //   cout << endl << v << endl;
   //   board.GetPossibleMoves(&possMoves);
   //   cout << board.GetValue() << endl;
   //
   //   m = board.CreateMove();
   //   *m = "(5, 2)";
   //   cout << "Applying the move " << (string)(*m) << endl;
   //   board.ApplyMove(m);
   //   cout << endl << v << endl;
   //   board.GetPossibleMoves(&possMoves);
   //   cout << board.GetValue() << endl;
   //   // END OF DEBUGGING CODE
   //
   //   cout << "Undoing" << endl;
   //   board.UndoLastMove();
   //   cout << endl << v << endl;
   //   board.GetPossibleMoves(&possMoves);
   //   cout << "Value: " << board.GetValue() << endl;
   //


   // Main loop
   do {
      bool valid = true;
      // Print the game board using the OthelloView object
      cout << v << endl;
      string player = board.GetNextPlayer() == 1 ? "Black" : "White";
      cout << player << "'s move" << endl;
      // Print all possible moves
      board.GetPossibleMoves(&possMoves);
      for (OthelloMove *moves : possMoves) {
         cout << (string)(*moves) << " ";
      }
      do {
         // Ask to input a command
         cout << endl << "Enter a command: ";
         string command, values;
         cin >> command;
         try {
            getline(cin, values);
            values = values.substr(1, values.length());
         }
         catch(exception &e) {
         }
         // Command loop:
         // move (r,c)
         // undo n
         // showValue
         // showHistory
         // quit
         if (command == "move") {
            OthelloMove *m = board.CreateMove();
            try {
               *m = values;
               bool possible = false;
               for (OthelloMove *moves : possMoves) {
                  if (*moves == *m) {
                     cout << "DEBUG OUTPUT: you entered \"move " <<
                        (string)(*m) << "\"" << endl;
                     board.ApplyMove(m);
                     possible = true;
                     valid = true;
                     break;
                  }
               }
               if (!possible) {
                  cout << "DEBUG OUTPUT: you entered \"move " <<
                     (string)(*m) << "\"" << endl;
                  cout << endl << "Not a valid move!" << endl;
                  valid = false;
                  delete m;
               }
            }
            catch (OthelloException &e) {
               delete m;
               cout << e.what() << endl;
            }
         }
         else if (command == "undo") {
            cout << "DEBUG OUTPUT: you entered \"undo " << values << "\"" << endl;
            if ((unsigned int)atoi(values.c_str()) >
            board.GetMoveHistory()->size()) {
               values = to_string(board.GetMoveCount());
            }
            for (int i = 0; i < atoi(values.c_str()); i++) {
               board.UndoLastMove();
            }
            valid = true;
         }
         else if (command == "showValue") {
            cout << "DEBUG OUTPUT: you entered \"showValue\"" << endl;
            cout << endl << "Board value: " << board.GetValue() << endl;
         }
         else if (command == "showHistory") {
            cout << "DEBUG OUTPUT: you entered \"showHistory\"" << endl;
            string histPlayer = board.GetNextPlayer() == 1 ? "White" : "Black";
            const vector<OthelloMove *>* history = board.GetMoveHistory();
            for (vector<OthelloMove *> ::const_reverse_iterator itr =
               history->rbegin(); itr != history->rend(); itr++) {
               cout << histPlayer << ": " << (string)(**itr) << endl;
               histPlayer = histPlayer == "White" ? "Black" : "White";
            }
         }
         else if (command == "quit") {
            break;
         }
         if (valid) {
            for (OthelloMove *moves : possMoves) {
               delete moves;
            }
            possMoves.clear();
         }
      } while (!valid);
   } while (!board.IsFinished()); 

   if (board.GetValue() > 0) {
      cout << endl << "Black Wins!" << endl;
   }
   else if (board.GetValue() < 0) {
      cout << endl << "White Wins!" << endl;
   }
   else {
      cout << endl << "Tie!" << endl;
   }
}
