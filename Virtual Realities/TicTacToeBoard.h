#ifndef __TICTACTOEBOARD_H
#define __TICTACTOEBOARD_H

#include <vector>
#include "TicTacToeMove.h"
#include "GameBoard.h"
#include "GameMove.h"

const int BOARD_SIZE_T = 3;
const int MAX_PLAYS_T = 9;
const int X_COUNT = 3;
const int O_COUNT = 3;

/*
An TicTacToeBoard encapsulates data needed to represent a single game of TicTacToe.
This includes the state of the board, tracking the current player, and keeping
a history of moves on the board.
*/
class TicTacToeBoard : public GameBoard {

public:
   enum Player {EMPTY = 0, X = 1, O = -1};

   // Default constructor initializes the board to its starting "new game" state
   TicTacToeBoard();

   /*
   Fills in a vector with all possible moves on the current board state for
   the current player. The moves should be ordered based first on row, then on
   column. Example ordering: (0, 5) (0, 7) (1, 0) (2, 0) (2, 2) (7, 7).
   If no moves are possible, then a single TicTacToeMove representing a Pass is
   put in the vector.
   Precondition: the vector is empty.
   Postcondition: the vector contains all valid moves for the current player.
   */
   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;

   /*
   Applies a valid move to the board, updating the board state accordingly.
   You may assume that this move is valid, and is consistent with the list
   of possible moves returned by GetAllMoves.
   */
   virtual void ApplyMove(GameMove *move);

   /*
   Undoes the last move applied to the board, restoring it to the state it was
   in prior to the most recent move.
   */
   virtual void UndoLastMove();

   /*
   Creates an TicTacToeMove object on the heap. Whoever calls this method is
   responsible for managing the move's lifetime (or transferring that task to
   someone else.)
   */
   virtual GameMove *CreateMove() const {return new TicTacToeMove;}

   inline static bool InBounds(int row, int col) {
      return row >= 0 && row < BOARD_SIZE_T && col >= 0 && col < BOARD_SIZE_T;
   }

   // Returns true if the game is finished.
   virtual bool IsFinished() const;

   std::string GetPlayerString(char player) {
      return (player == 1 ? "X" : "O");
   }

private:
   friend class TicTacToeView;

   bool IsThreeInARow() const;

   // NOTE: we inherit mNextPlayer, mValue, and mHistory from GameBoard.
   char mBoard[BOARD_SIZE_T][BOARD_SIZE_T];
};
#endif
