#include <iostream>
#include "OthelloGame.h"

using namespace std;

int main(int argc, char* argv[]) {

   int row = 0, col = 0, currentPlayer = 1, value;
   bool playing = true, bPass = false, wPass = false;

   char board[BOARD_SIZE][BOARD_SIZE] = {
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, -1, 1, 0, 0, 0},
      {0, 0, 0, 1, -1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
   };
   cout << "Welcome to Othello!" << endl;
   PrintBoard(board);
   while (playing) {
      if (currentPlayer == 1) {
         cout << "Black's turn. Please choose a move: " << endl;
         GetMove(&row, &col);
      }
      else if (currentPlayer == -1) {
         cout << "White's turn. Please choose a move: " << endl;
         GetMove(&row, &col);
      }
      while (!IsValidMove(board, row, col)) {
         cout << "Invalid Move. Please choose a move: " << endl;
         GetMove(&row, &col);
      }
      if (row == -1 && col == -1) {
         if (currentPlayer == 1) {
            bPass = true;
         }
         else if (currentPlayer == -1) {
            wPass = true;
         }
      }
      else {
         ApplyMove(board, row, col, currentPlayer);
      }
      if (bPass && wPass) {
         value = GetValue(board);
         if (value > 0) {
            cout << "\nGame over. Black wins!" << endl;
         }
         else if (value < 0) {
            cout << "\nGame over. White wins!" << endl;
         }
         else if (value == 0) {
            cout << "\nGame over. We have a tie!" << endl;
         }
         playing = false;
      }
      else {
         PrintBoard(board);
      }
      if (row != -1 && col != -1 && ((bPass && !wPass) || (!bPass && wPass))) {
         cout << "Reset" << endl;
         bPass = false, wPass = false;
      }
      currentPlayer = currentPlayer == 1 ? -1 : 1;
   }
}
