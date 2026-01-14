#include <iostream>
using namespace std;

const int SIZE = 9;

// Function to print the Sudoku board
void printBoard(int board[SIZE][SIZE]) {
    cout << "\nSudoku Board:\n";
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0 && i != 0)
            cout << "---------------------\n";

        for (int j = 0; j < SIZE; j++) {
            if (j % 3 == 0 && j != 0)
                cout << "| ";

            if (board[i][j] == 0)
                cout << ". ";
            else
                cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Check if number exists in row
bool usedInRow(int board[SIZE][SIZE], int row, int num) {
    for (int col = 0; col < SIZE; col++)
        if (board[row][col] == num)
            return true;
    return false;
}

// Check if number exists in column
bool usedInCol(int board[SIZE][SIZE], int col, int num) {
    for (int row = 0; row < SIZE; row++)
        if (board[row][col] == num)
            return true;
    return false;
}

// Check if number exists in 3x3 box
bool usedInBox(int board[SIZE][SIZE], int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (board[row + startRow][col + startCol] == num)
                return true;
    return false;
}

// Check if placing number is safe
bool isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    return !usedInRow(board, row, num) &&
           !usedInCol(board, col, num) &&
           !usedInBox(board, row - row % 3, col - col % 3, num);
}

// Find an empty cell
bool findEmptyLocation(int board[SIZE][SIZE], int &row, int &col) {
    for (row = 0; row < SIZE; row++)
        for (col = 0; col < SIZE; col++)
            if (board[row][col] == 0)
                return true;
    return false;
}

// Sudoku Solver using Backtracking
bool solveSudoku(int board[SIZE][SIZE]) {
    int row, col;

    if (!findEmptyLocation(board, row, col))
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board))
                return true;

            board[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int board[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int choice;
    do {
        printBoard(board);
        cout << "\nMenu:\n";
        cout << "1. Enter a number\n";
        cout << "2. Solve Sudoku\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            int row, col, num;
            cout << "Enter row (1-9): ";
            cin >> row;
            cout << "Enter column (1-9): ";
            cin >> col;
            cout << "Enter number (1-9): ";
            cin >> num;

            row--; col--;

            if (row < 0 || row >= 9 || col < 0 || col >= 9 || num < 1 || num > 9) {
                cout << "Invalid input!\n";
            } else if (board[row][col] != 0) {
                cout << "Cell already filled!\n";
            } else if (isSafe(board, row, col, num)) {
                board[row][col] = num;
            } else {
                cout << "Invalid move!\n";
            }
        }
        else if (choice == 2) {
            if (solveSudoku(board)) {
                cout << "\nSudoku Solved Successfully!\n";
                printBoard(board);
            } else {
                cout << "No solution exists.\n";
            }
        }

    } while (choice != 3);

    return 0;
}
