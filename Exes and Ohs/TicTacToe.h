// PrintBoard takes a 2-dimensional array parameter representing the game state
// and prints it to cout. See the spec for details on formatting the output.
void PrintBoard(char board[3][3]);

// GetMove uses cin to read the user's choice for where to move next on the 
// board. It does NOT update the game board with the move choice; it simply
// scans in values to the row and col variables, which will update whatever
// variables were used as arguments in the main. Do not check move validity
// in this function.
void GetMove(int *row, int *col);

// MoveIsValid returns true if the board is empty at the requested row/col,
// and false otherwise. Used in main to see if the move is valid and alert
// the user if it is not.
bool MoveIsValid(char board[3][3], int row, int col);

char GetBoardChar(char boardChar);

bool CheckWinner(char board[3][3]);
