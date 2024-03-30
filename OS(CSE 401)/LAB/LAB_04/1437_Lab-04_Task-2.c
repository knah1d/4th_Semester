#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ROWS 3
#define COLS 3

void multiplyRow(int row, int matrix1[ROWS][COLS], int matrix2[ROWS][COLS], int result[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        int sum = 0;
        for (int j = 0; j < COLS; j++) {
            sum += matrix1[row][j] * matrix2[j][i];
        }
        result[row][i] = sum;
    }

    for (int i = 0; i < ROWS; i++) {
        printf("%d\t", result[row][i]);
    }
    printf("\n");
}

int main() {
    int matrix1[ROWS][COLS] = {{4, 9, 3}, {4, 7, 6}, {7, 5, 9}};
    int matrix2[ROWS][COLS] = {{9, 5, 7}, {6, 3, 4}, {3, 4, 1}};
    int result[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        pid_t pid = fork();

        if (pid == 0) { // Child process
            multiplyRow(i, matrix1, matrix2, result);
            exit(0);
        } else { // Parent process
            wait(NULL);
        }
    }

    return 0;
}

