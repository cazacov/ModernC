#include <stdio.h>
#include <stdlib.h>

void print_array(int array[static 1], size_t size);

int *merge_sort(int *array, int *buffer, size_t left, size_t right);

int main() {

    int array[30];
    int buffer[30];
    size_t array_size = sizeof(array) / sizeof(array[0]);

    // Initialize array with some random data
    for (size_t i = 0; i < array_size; i++) {
        array[i] = rand() % 1000;
    }

    printf("Initial state:\n");
    print_array(array, array_size);

    int *result = merge_sort(array, buffer, 0, array_size - 1);

    printf("Final state:\n");
    print_array(result, array_size);

    return 0;
}

// Merge sort: https://de.wikipedia.org/wiki/Mergesort
int *merge_sort(int *array, int *buffer, size_t left, size_t right) {
    if (left == right) {
        buffer[left] = array[left];
        return buffer;
    }

    size_t middle = (left + right) / 2;

    int *left_buff = merge_sort(array, buffer, left, middle);
    int *right_buff = merge_sort(array, buffer, middle + 1, right);

    int *target = left_buff == array ? buffer : array;

    size_t l_cur = left;
    size_t r_cur = middle + 1;

    for (size_t i = left; i <= right; i++) {
        if (l_cur <= middle && r_cur <= right) {
            if (left_buff[l_cur] < right_buff[r_cur]) {
                target[i] = left_buff[l_cur++];
            } else {
                target[i] = right_buff[r_cur++];
            }
        } else if (l_cur <= middle) {
            target[i] = left_buff[l_cur++];
        } else {
            target[i] = right_buff[r_cur++];
        }
    }
    return target;
}


void print_array(int array[static 1], size_t size) {

    for (size_t i = 0; i < size; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}