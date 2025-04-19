#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct sort_args {
    int* arr_start;
    int* arr_end;
};

void* merge_sort(void* arg) {
    struct sort_args* args = (struct sort_args*)arg;

    // If the array has 1 or 0 elements, it's already sorted
    if (args->arr_start >= args->arr_end)
        pthread_exit(NULL);

    // Split the array into two halves
    struct sort_args left_args, right_args;
    left_args.arr_start = args->arr_start;
    left_args.arr_end = args->arr_start + (args->arr_end - args->arr_start) / 2;
    right_args.arr_start = left_args.arr_end + 1;
    right_args.arr_end = args->arr_end;

    // Create threads for each half
    pthread_t left_thread, right_thread;
    pthread_create(&left_thread, NULL, merge_sort, &left_args);
    pthread_create(&right_thread, NULL, merge_sort, &right_args);
    pthread_join(left_thread, NULL);
    pthread_join(right_thread, NULL);

    // Merge the two halves
    int size = right_args.arr_end - left_args.arr_start + 1;
    int* temp = (int*)malloc(size * sizeof(int));
    if (temp == NULL) {
        perror("Failed to allocate memory for merging");
        pthread_exit(NULL);
    }
    int *left = left_args.arr_start, *right = right_args.arr_start;
    int* now = temp;
    while (left <= left_args.arr_end && right <= right_args.arr_end) {
        if (*left < *right)
            *now++ = *left++;
        else
            *now++ = *right++;
    }
    while (left <= left_args.arr_end)
        *now++ = *left++;
    while (right <= right_args.arr_end)
        *now++ = *right++;
    for (int i = 0; i < size; i++)
        *(args->arr_start + i) = temp[i];
    free(temp);

    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    // Read the size of the array
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    // Allocate memory for the array
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        perror("Failed to allocate memory for array");
        return 1;
    }

    // Read the elements of the array
    printf("Enter %d elements of the array: ", size);
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    // Create a thread to sort the array
    struct sort_args args;
    args.arr_start = arr, args.arr_end = arr + size - 1;
    pthread_t thread;
    if (pthread_create(&thread, NULL, merge_sort, &args) != 0) {
        perror("Failed to create thread");
        free(arr);
        return 1;
    }

    // Wait for the thread to finish
    if (pthread_join(thread, NULL) != 0) {
        perror("Failed to join thread");
        free(arr);
        return 1;
    }

    // Print the sorted array
    printf("Sorted array:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // Free the allocated memory
    free(arr);

    return 0;
}
