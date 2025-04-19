#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

struct sudoku_args {
    int bag[SIZE];  // count of numbers 1-9
    int results;    // 0 for invalid, 1 for valid.
};

void* check(void* arg) {
    struct sudoku_args* args = (struct sudoku_args*)arg;

    // Check if the bag contains all numbers from 1 to 9
    int* bag = args->bag;
    args->results = 1;
    for (int i = 0; i < SIZE; i++) {
        if (bag[i] != 1) {
            args->results = 0;
            break;
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        printf("Usage: %s <sudoku_file>\n", argv[0]);
        return 1;
    }

    // Read the file
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // Read the Sudoku board from the file
    int board[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (fscanf(file, "%d", &board[i][j]) != 1) {
                fprintf(stderr, "Invalid Sudoku board format.\n");
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);

    // 9 rows + 9 columns + 9 boxes
    pthread_t threads[SIZE * 3];
    struct sudoku_args args[SIZE * 3];

    // Initialize thread arguments
    for (int i = 0; i < SIZE * 3; i++) {
        args[i].results = 1;
        for (int j = 0; j < SIZE; j++)
            args[i].bag[j] = 0;
    }

    // Check rows
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            args[i].bag[board[i][j] - 1]++;
        }
    }

    // Check columns
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            args[i + SIZE].bag[board[j][i] - 1] = 1;
        }
    }

    // Check boxes
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int row = (i / 3) * 3 + (j / 3);
            int col = (i % 3) * 3 + (j % 3);
            args[i + SIZE * 2].bag[board[row][col] - 1]++;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < SIZE * 3; i++) {
        if (pthread_create(&threads[i], NULL, check, &args[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }
    for (int i = 0; i < SIZE * 3; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    // Check results
    int valid = 1;
    for (int i = 0; i < SIZE * 3; i++)
        valid &= args[i].results;

    // Print the result
    if (valid)
        printf("The Sudoku board is valid.\n");
    else
        printf("The Sudoku board is invalid.\n");

    return 0;
}
