#include "GameExceptions.h"
#include "GameBoard.h"
#include "GameView.h"
#include "GameMove.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include "TicTacToeBoard.h"
#include "TicTacToeView.h"
#include "TicTacToeMove.h"
#include "ConnectFourBoard.h"
#include "ConnectFourView.h"
#include "ConnectFourMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


int main(int argc, char* argv[]) {
   // Initialization
   GameBoard *board; // the state of the game board
   GameView *v; // a View for outputting the board via operator<<
   string userInput; // a string to hold the user's command choice
   vector<GameMove *> possMoves; // a holder for possible moves

   bool exit = false;
   while (!exit) {
      int userChoice;
      bool choiceIsValid = false, quit = false;
      while (!choiceIsValid) {
         cout << "Which game do you want to play?" << endl;
         cout << "1. Othello\n2. Tic Tac Toe\n3. Connect Four\n4. Exit" << endl;
         cin >> userChoice;
         if (userChoice == 1) {
            board = new OthelloBoard();
            v = new OthelloView(board);
            choiceIsValid = true;
         }
         else if (userChoice == 2) {
            board = new TicTacToeBoard();
            v = new TicTacToeView(board);
            choiceIsValid = true;
         }
         else if (userChoice == 3) {
            board = new ConnectFourBoard();
            v = new ConnectFourView(board);
            choiceIsValid = true;
         }
         else if (userChoice == 4) {
            exit = true;
            choiceIsValid = true;
            break;
         }
         else {
            cout << "Invalid Choice!" << endl;
         }
      }
      if (exit) {
         break;
      }
      // Main loop
      do {
         bool valid = true;
         // Print the game board using the GameView object
         cout << *v << endl;
         string player = "";
         if (userChoice == 1) {
            player = board->GetNextPlayer() == 1 ? "Black" : "White";
         }
         else if (userChoice == 2) {
            player = board->GetNextPlayer() == 1 ? "X" : "O";
         }
         else {
            player = board->GetNextPlayer() == 1 ? "Yellow" : "Red";
         }
         cout << player << "'s move" << endl;
         // Print all possible moves
         board->GetPossibleMoves(&possMoves);
         for (GameMove *moves : possMoves) {
            cout << static_cast<string>(*moves) << " ";
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
               GameMove *m = board->CreateMove();
               try {
                  *m = values;
                  bool possible = false;
                  for (GameMove *moves : possMoves) {
                     if (*moves == *m) {
                        cout << "DEBUG OUTPUT: you entered \"move " <<
                           static_cast<string>(*m) << "\"" << endl;
                        board->ApplyMove(m);
                        possible = true;
                        valid = true;
                        break;
                     }
                  }
                  if (!possible) {
                     cout << "DEBUG OUTPUT: you entered \"move " <<
                        static_cast<string>(*m) << "\"" << endl;
                     cout << endl << "Not a valid move!" << endl;
                     valid = false;
                     delete m;
                  }
               }
               catch (GameException &e) {
                  delete m;
                  cout << e.what() << endl;
               }
            }
            else if (command == "undo") {
               cout << "DEBUG OUTPUT: you entered \"undo " << values
                  << "\"" << endl;
               if ((unsigned int)atoi(values.c_str()) >
               board->GetMoveHistory()->size()) {
                  values = to_string(board->GetMoveCount());
               }
               for (int i = 0; i < atoi(values.c_str()); i++) {
                  board->UndoLastMove();
               }
               valid = true;
            }
            else if (command == "showValue") {
               cout << "DEBUG OUTPUT: you entered \"showValue\"" << endl;
               cout << endl << "Board value: " << board->GetValue() << endl;
            }
            else if (command == "showHistory") {
               cout << "DEBUG OUTPUT: you entered \"showHistory\"" << endl;
               string histPlayer = "";
               if (userChoice == 1) {
                  histPlayer = board->GetNextPlayer() == 1 ? "White" : "Black";
               }
               else if (userChoice == 2) {
                  histPlayer = board->GetNextPlayer() == 1 ? "O" : "X";
               }
               else {
                  histPlayer = board->GetNextPlayer() == 1 ? "Red" : "Yellow";
               }
               const vector<GameMove *>* history = board->GetMoveHistory();
               for (vector<GameMove *> ::const_reverse_iterator itr =
                  history->rbegin(); itr != history->rend(); itr++) {
                  cout << histPlayer << ": " << (string)(**itr) << endl;
                  if (userChoice == 1) {
                     histPlayer = histPlayer == "White" ? "Black" : "White";
                  }
                  else if (userChoice == 2) {
                     histPlayer = histPlayer == "O" ? "X" : "O";
                  }
                  else {
                     histPlayer = histPlayer == "Red" ? "Yellow" : "Red";
                  }
               }
            }
            else if (command == "quit") {
               quit = true;
               for (GameMove *moves : possMoves) {
                  delete moves;
               }
               possMoves.clear();
               break;
            }
            if (valid) {
               for (GameMove *moves : possMoves) {
                  delete moves;
               }
               possMoves.clear();
            }
         } while (!valid);
      } while (!board->IsFinished() && !quit);

      if (userChoice == 2 || userChoice == 3) {
         cout << *v << endl;
      }

      if (board->GetValue() > 0) {
         if (userChoice == 1) {
            cout << endl << "Black Wins!" << endl;
         }
         else if (userChoice == 2) {
            cout << endl << "X Wins!" << endl;
         }
         else {
            cout << endl << "Yellow Wins!" << endl;
         }
      }
      else if (board->GetValue() < 0) {
         if (userChoice == 1) {
            cout << endl << "White Wins!" << endl;
         }
         else if (userChoice == 2) {
            cout << endl << "O Wins!" << endl;
         }
         else {
            cout << endl << "Red Wins!" << endl;
         }
      }
      else {
         cout << endl << "Tie!" << endl;
      }
      delete board;
   }
}
