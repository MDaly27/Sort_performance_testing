#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes for sorting algorithms
void bubble_sort(int arr[], int n);
void quick_sort(int arr[], int low, int high);
void merge_sort(int arr[], int l, int r);
void heap_sort(int arr[], int n);

// Utility functions
void heapify(int arr[], int n, int i);
void fill_array(int arr[], int n);
void copy_array(int source[], int dest[], int n);
void print_results(char* algo, int n, double time_spent);

// Timer function
double time_sorting(void (*sort_func)(int*, int), int arr[], int n);
double time_quick_sort(int arr[], int low, int high);
double time_merge_sort(int arr[], int l, int r);
double time_heap_sort(int arr[], int n);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <array_size>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int* arr = malloc(n * sizeof(int)); // unsorted array
    int* temp = malloc(n * sizeof(int));// this array will be recopied as unsorted, then sorted for each algorithm

    fill_array(arr, n);

    // Bubble Sort
    copy_array(arr, temp, n);
    double bubble_time = time_sorting(bubble_sort, temp, n);
    print_results("Bubble Sort", n, bubble_time);

    // Quick Sort
    copy_array(arr, temp, n);
    double quick_time = time_quick_sort(temp, 0, n - 1);
    print_results("Quick Sort", n, quick_time);

    // Merge Sort
    copy_array(arr, temp, n);
    double merge_time = time_merge_sort(temp, 0, n - 1);
    print_results("Merge Sort", n, merge_time);

    // Heap Sort
    copy_array(arr, temp, n);
    double heap_time = time_heap_sort(temp, n);
    print_results("Heap Sort", n, heap_time);

    free(arr);
    free(temp);
    return 0;
}

// Sorting Algorithms Implementations

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}




void heap_sort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}


// Helper Functions

void fill_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

void copy_array(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

double time_sorting(void (*sort_func)(int*, int), int arr[], int n) {
    clock_t start = clock();
    sort_func(arr, n);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

double time_quick_sort(int arr[], int low, int high) {
    clock_t start = clock();
    quick_sort(arr, low, high);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

double time_merge_sort(int arr[], int l, int r) {
    clock_t start = clock();
    merge_sort(arr, l, r);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

double time_heap_sort(int arr[], int n) {
    clock_t start = clock();
    heap_sort(arr, n);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}




// helper function to ensure max heap structure for heap sort
void heapify(int arr[], int n, int i) {
    int largest = i;            // Initialize largest as root
    int left = 2 * i + 1;       // Left child
    int right = 2 * i + 2;      // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than the largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected subtree
        heapify(arr, n, largest);
    }
}


void print_results(char* algo, int n, double time_spent) {
    printf("%s,%d,%f\n", algo, n, time_spent);
}

