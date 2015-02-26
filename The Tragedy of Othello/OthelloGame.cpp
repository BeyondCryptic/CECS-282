#include <iostream>
#include "OthelloGame.h"

using namespace std;

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
   for (int xNext = -1; xNext <= 1; xNext++) {
      for (int yNext = -1; yNext <= 1; yNext++) {
         if (xNext != 0 || yNext != 0) {
            int xNew = row + xNext, yNew = col + yNext, count = 0;
            while (InBounds(xNew, yNew) && board[xNew][yNew] != 0) {
               int xPrev = xNew - xNext, yPrev = yNew - yNext;
               if (board[xNew][yNew] != currentPlayer) {
                  count += 1;
               }
               while (board[xNew][yNew] == currentPlayer && count > 0) {
                  board[xPrev][yPrev] = currentPlayer;
                  xPrev -= xNext;
                  yPrev -= yNext;
                  count -= 1;
               }
               if (board[xNew][yNew] == currentPlayer && count == 0) {
                  break;
               }
               xNew += xNext;
               yNew += yNext;
            }
            xNew = row + xNext;
            yNew = col + yNext;
         }
      }
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
