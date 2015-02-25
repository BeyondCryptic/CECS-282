#include <iostream>
#include "OthelloGame.h"

using namespace std;

int main(int argc, char* argv[]) {

   int row = 0, col = 0, currentPlayer = 1;
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
         if (GetValue(board) > 0) {
            cout << "\nGame over. Black wins!" << endl;
         }
         else if (GetValue(board) < 0) {
            cout << "\nGame over. White wins!" << endl;
         }
         else if (GetValue(board) == 0) {
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

void PrintBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
   cout << "\n- 0 1 2 3 4 5 6 7" << endl;
   for (int i = 0; i < BOARD_SIZE; i++) {
      cout << i << " ";
      for (int j = 0; j < BOARD_SIZE; j++) {
         if (board[i][j] == 0) {
            cout << '.' << " ";
         }
         else if (board[i][j] == 1) {
            cout << 'B' << " ";
         }
         else if (board[i][j] == -1) {
            cout << 'W' << " ";
         }
      }
      cout << endl;
   }
   cout << endl;
}

bool InBounds(int row, int col) {
   return ((row >= BOARD_SIZE || row < 0) || (col >= BOARD_SIZE || col < 0))
      ? false : true;
}

bool IsValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
   return ((row == -1 && col == -1) ||
      (InBounds(row, col) && board[row][col] == 0)) ? true : false;
}

void GetMove(int *row, int *col) {
   char x;
   cin >> x >> *row >> x >> *col >> x;
}

void ApplyMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col,
   char currentPlayer) {
   board[row][col] = currentPlayer;
   int xNext = -1, yNext = -1, count = 0;
   while (xNext <= 1) {
      yNext = -1;
      while (yNext <= 1) {
         if (xNext != 0 || yNext != 0) {
            int xNew = row + xNext, yNew = col + yNext;
            while (InBounds(xNew, yNew) && board[xNew][yNew] != 0) {
               int xPrev = xNew - xNext, yPrev = yNew - yNext;
               if (board[xNew][yNew] != currentPlayer) {
                  count += 1;
               }
               while (board[xNew][yNew] == currentPlayer && count > 0) {
                  board[xPrev][yPrev] = currentPlayer;
                  xPrev -= xNext, yPrev -= yNext, count -= 1;
               }
               if (board[xNew][yNew] == currentPlayer && count == 0) {
                  break;
               }
               xNew += xNext, yNew += yNext;
            }
            count = 0, xNew = row + xNext, yNew = col + yNext;
         }
         yNext = yNext > 1 ? -1 : yNext+1;
      }
      xNext++;
   }
}

int GetValue(char board[BOARD_SIZE][BOARD_SIZE]) {
   int v = 0;
   for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) {
      v = (board[0][i] == 1) ? (v + 1) : (v);
      v = (board[0][i] == -1) ? (v - 1) : (v);
   }
   return v;
}
