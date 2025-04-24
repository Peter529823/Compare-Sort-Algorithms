#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

// Function to measure the execution time of a sorting algorithm
// Parameters:
// - sortFunc: The sorting function to be measured
// - arr: The array to be sorted
// - sortName: The name of the sorting algorithm (for display purposes)
template<typename Func>
void measureTime(Func sortFunc, std::vector<int> arr, const std::string& sortName) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << sortName << " took " << elapsed.count() << " ms\n";
}

// Selection Sort: A simple comparison-based sorting algorithm
// Time Complexity: O(n^2)
template<typename T>
void selectionSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

// Merge Sort: A divide-and-conquer sorting algorithm
// Time Complexity: O(n log n)
template<typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
    std::vector<T> leftVec(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<T> rightVec(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < leftVec.size() && j < rightVec.size()) {
        arr[k++] = (leftVec[i] < rightVec[j]) ? leftVec[i++] : rightVec[j++];
    }
    while (i < leftVec.size()) arr[k++] = leftVec[i++];
    while (j < rightVec.size()) arr[k++] = rightVec[j++];
}

template<typename T>
void mergeSortHelper(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

template<typename T>
void mergeSort(std::vector<T>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// Quick Sort: A divide-and-conquer sorting algorithm
// Time Complexity: O(n log n) on average, O(n^2) in the worst case
template<typename T>
int partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) std::swap(arr[++i], arr[j]);
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<typename T>
void quickSortHelper(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSortHelper(arr, low, p - 1);
        quickSortHelper(arr, p + 1, high);
    }
}

template<typename T>
void quickSort(std::vector<T>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}

// Heap Sort: A comparison-based sorting algorithm using a binary heap
// Time Complexity: O(n log n)
template<typename T>
void heapify(std::vector<T>& arr, int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template<typename T>
void heapSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Function to generate a random array of integers
// Parameters:
// - size: The size of the array
// - min: The minimum value of the random integers
// - max: The maximum value of the random integers
std::vector<int> generateRandomArray(int size, int min = 1, int max = 100000) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    for (int& x : arr) x = dist(gen);
    return arr;
}

int main() {
    // Main function to test sorting algorithms on arrays of different sizes
    // Array sizes: 1000, 5000, 10000, and 20000
    std::vector<int> sizes = {1000, 5000, 10000, 20000};

    for (int size : sizes) {
        std::cout << "\nArray size: " << size << "\n";
        auto original = generateRandomArray(size);

        // Measure and display the execution time of each sorting algorithm
        measureTime(selectionSort<int>, original, "Selection Sort");
        measureTime(mergeSort<int>, original, "Merge Sort");
        measureTime(quickSort<int>, original, "Quick Sort");
        measureTime(heapSort<int>, original, "Heap Sort");
    }

    return 0;
}
