#include <iostream>
#include "TicTacToe.h"

using namespace std;

int main(int argc, char* argv[]) {

   int row, col;
   bool xWent = false;
   bool gameOver = false;
   int counter = 9;

   char board[3][3] = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
   };

   PrintBoard(board);

   while (!gameOver) {

      // Start Game Logic

      bool valid = false;

      while (!valid) {
         if (!xWent) {
            cout << "X's turn: ";
         }
         else {
            cout << "O's turn: ";
         }
         GetMove(&row, &col);
         while ((row > 2 || row < 0) || (col > 2 || col < 0)) {
            cout << "Please enter a valid range!" << endl;
            if (!xWent) {
               cout << "X's turn: ";
            }
            else {
               cout << "O's turn: ";
            }
            GetMove(&row, &col);
         }

         if (MoveIsValid(board, row, col)) {
            if (!xWent) {
               board[row][col] = 1;
               valid = true;
            }
            else {
               board[row][col] = -1;
               valid = true;
            }
         }
      }

      // End Logic

      PrintBoard(board);
      counter--;
      if (counter == 0) {
         gameOver = true;
      }

      xWent = !xWent;

   }
}

void PrintBoard(char board[3][3]) {
   cout << "- 0 1 2" << endl;
   cout << "0" << " " << GetBoardChar(board[0][0]) << " " <<
      GetBoardChar(board[0][1]) << " " << GetBoardChar(board[0][2]) << endl;
   cout << "1" << " " << GetBoardChar(board[1][0]) << " " <<
      GetBoardChar(board[1][1]) << " " << GetBoardChar(board[1][2]) << endl;
   cout << "2" << " " << GetBoardChar(board[2][0]) << " " <<
      GetBoardChar(board[2][1]) << " " << GetBoardChar(board[2][2]) << endl;
}

void GetMove(int *row, int *col) {
   cin >> *row;
   cin.ignore(1, ',');
   cin >> *col;
}

bool MoveIsValid(char board[3][3], int row, int col) {
   if (board[row][col] != 1 && board[row][col] != -1) {
      return true;
   }
   else {
      cout << "That space is already taken!" << endl;
      return false;
   }
}

char GetBoardChar(char boardChar) {
   if (boardChar == 1) {
      return 'X';
   }
   if (boardChar == -1) {
      return 'O';
   }
   else {
      return '.';
   }
}
