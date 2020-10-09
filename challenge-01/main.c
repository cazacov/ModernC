#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#define SWAP(x,y) do {   \
   typeof(x) _x = x;      \
   typeof(y) _y = y;      \
   x = _y;                \
   y = _x;                \
 } while(0)

void print_array(int array[static 1], size_t size);
void init_random(int array[], size_t array_size);

int *merge_sort(int *array, int *buffer, size_t left, size_t right);

size_t partition(int array[], size_t low, size_t high);
void quickSort(int array[], size_t low, size_t high);

bool is_sorted(int array[static 1], size_t size);

int main() {

    const int N = 300;

    int array[N];
    int buffer[N];
    size_t array_size = sizeof(array) / sizeof(array[0]);

    // Initialize array with some random data
    init_random(array, array_size);
    printf("Initial state:\n");
    print_array(array, array_size);

    int *result = merge_sort(array, buffer, 0, array_size - 1);

    printf("Sorted with merge sort:\n");
    print_array(result, array_size);
    printf("Order check %s\n\n\n", is_sorted(result, array_size) ? "PASSED" : "FAILED");

    init_random(array, array_size);
    printf("Initial state:\n");
    print_array(array, array_size);

    quickSort(array, 0, array_size - 1);
    printf("Sorted with quick sort:\n");
    print_array(array, array_size);
    printf("Order check %s\n", is_sorted(array, array_size) ? "PASSED" : "FAILED");

    return 0;
}

void quickSort(int array[], size_t low, size_t high) {
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        size_t pi = partition(array, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
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
        if (i) {
            printf("\t%d", array[i]);
        }
        else {
            printf("%d", array[i]);
        }
    }
    printf("\n");
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
// Initializes array with random values
void init_random(int array[], size_t array_size) {
    for (size_t i = 0; i < array_size; i++) {
        array[i] = rand() % 1000;
    }
}
#pragma clang diagnostic pop

size_t partition(int *array, size_t low, size_t high) {
    int pivot = array[high];    // pivot
    ptrdiff_t  i = (low - 1);  // Index of smaller element

    for (size_t j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (array[j] <= pivot)
        {
            i++;    // increment index of smaller element
            SWAP(array[i], array[j]);
        }
    }
    SWAP(array[i + 1], array[high]);
    return (i + 1);
}

bool is_sorted(int *array, size_t size) {
    if (size <= 1) {
        return true;
    }

    int previous = array[0];
    int *ptr = array + 1;
    size_t n = size - 1;

    while (n--) {
        int next = *ptr;
        if (next < previous) {
            return false;
        }
        previous = next;
        ptr++;
    }
    return true;
}
