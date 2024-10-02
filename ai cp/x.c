#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int N;  // Size of the board (can now be taken as input)

// Function to print the solution board
void printSolution(int **board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf(" %d ", board[i][j]);
        printf("\n");
    }
}

// Function to check if it's safe to place a queen at board[row][col]
bool isSafe(int **board, int row, int col) {
    int i, j;

    // Check this row on the left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on the left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

// Utility function to solve the N-Queens problem using backtracking
bool solveNQUtil(int **board, int col) {
    if (col >= N)
        return true;

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;

            if (solveNQUtil(board, col + 1))
                return true;

            board[i][col] = 0;  // Backtrack
        }
    }
    return false;
}

// Function to solve the N-Queens problem
bool solveNQ() {
    // Dynamically allocate memory for the board based on user input
    int **board = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        board[i] = (int *)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++)
            board[i][j] = 0;  // Initialize the board to 0
    }

    if (solveNQUtil(board, 0)) {
        printSolution(board);
        // Free dynamically allocated memory
        for (int i = 0; i < N; i++)
            free(board[i]);
        free(board);
        return true;
    }

    printf("Solution does not exist\n");
    // Free dynamically allocated memory
    for (int i = 0; i < N; i++)
        free(board[i]);
    free(board);
    return false;
}

// Main function
int main() {
    printf("Enter the size of the board (N): ");
    scanf("%d", &N);

    solveNQ();
    return 0;
}
