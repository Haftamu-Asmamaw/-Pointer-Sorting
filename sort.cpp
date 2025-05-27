#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace chrono;
void printPointers(int* arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << *arr[i] << " ";
    }
    cout << endl;
}
void bubbleSort(int* arr[], int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (*arr[j] > *arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}
void insertionSort(int* arr[], int size) {
    for (int i = 1; i < size; i++) {
        int* key = arr[i];
        int j = i - 1;
        while (j >= 0 && *arr[j] > *key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}
void quickSort(int* arr[], int low, int high) {
    if (low < high) {
        int* pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (*arr[j] < *pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i+1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void merge(int* arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int*> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (*L[i] <= *R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int* arr[], int l, int r) {
    if (l < r) {
        int m = (l + r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
template<typename Func>
void testSort(Func sortFunc, int* arr[], int size, const string& name) {
    int* temp[size];
    for (int i = 0; i < size; i++) temp[i] = arr[i];

    auto start = high_resolution_clock::now();
    sortFunc(temp, size);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    cout << name << " - Time: " << duration.count() << " microseconds\n";
}

int main() {
    const int size = 10;
    int data[size] = {42, 10, 4, 60, 9, 3, 21, 17, 50, 7};
    int* arr[size];
    for (int i = 0; i < size; i++) arr[i] = &data[i];
    
    testSort(bubbleSort, arr, size, "Bubble Sort");
    testSort(insertionSort, arr, size, "Insertion Sort");

    auto quickWrap = [](int* arr[], int size) {
        quickSort(arr, 0, size - 1);
    };
    testSort(quickWrap, arr, size, "Quick Sort");

    auto mergeWrap = [](int* arr[], int size) {
        mergeSort(arr, 0, size - 1);
    };
    testSort(mergeWrap, arr, size, "Merge Sort");

    return 0;
}
