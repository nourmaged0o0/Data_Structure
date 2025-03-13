#include <iostream>
using namespace std;

template<typename T>
class SortingSystem {
private:
    T *data; // Dynamic array for storing input data
    int size; // Size of the array

public:
    SortingSystem(int n) {
        this->data = new T[n];
        this->size = 0;
    }

    ~SortingSystem() {
        delete[] this->data;
    }

    void insertionSort() {
        T arr[size] = this->data;
        for (int i = 1; i < size; i++) {
            T temp = arr[i];
            int j = i - 1;
            while (j >= 0 && temp < arr[j]) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = temp;
        }
    } // (1) Insertion Sort
    void selectionSort() {
        T arr[size] = data;
        int minIndx;
        int n = size;
        for (int i = 0; i < n - 1; i++) {
            //{5,3,2,1}
            minIndx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIndx]) {
                    minIndx = j;
                    swap(arr[i], arr[minIndx]);
                }
            }
        }
    } // (2) Selection Sort
    void bubbleSort() {
        T arr[size] = data;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    } // (3) Bubble Sort
    void shellSort() {
        T arr[size] = data;
        for (int interval = size / 2; interval > 0; interval /= 2) {
            for (int i = interval; i < size; i++) {
                T temp = arr[i];
                int j;
                for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
                    arr[j] = arr[j - interval];
                }
                arr[j] = temp;
            }
        }
    } // (4) Shell Sort
    void mergeSort(int left, int right) {
        T arr[size] = this->data;
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    } // (5) Merge Sort
    void quickSort(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            quickSort(left, mid);
            quickSort(mid + 1, right);
        }

    }// (6) Quick Sort //// changes the data it self
    void countSort() {
        T arr[size];
        for (int i = 0; i < size; i++) {
            arr[i] = data[i];
        }

        int maxVal = arr[0];
        int minVal = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] > maxVal) maxVal = arr[i];
            if (arr[i] < minVal) minVal = arr[i];
        }

        int range = maxVal - minVal + 1;
        int* count = new int[range]{0};
        for (int i = 0; i < size; i++) {
            count[arr[i] - minVal]++;
        }
        int index = 0;
        for (int i = 0; i < range; i++) {
            while (count[i]-- > 0) {
                arr[index++] = i + minVal;
            }
        }
        delete[] count;



    } // (7) Count Sort (Only for int)
    void radixSort(); // (8) Radix Sort (Only for int)
    void bucketSort(); // (9) Bucket Sort

    void merge(int left, int mid, int right) {
        T arr[size] = this->data;
        int n1 = mid - left + 1;
        int n2 = right - mid;
        T *L = new T[n1], *R = new T[n2];

        int i, j, k;
        for (i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        i = j = 0;
        k = left;

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
        delete[] L;
        delete[] R;
    } // Merge Sort Helper
    int partition(int low, int high) {
        int pivot = data[low];
        int i = low;
        for (int j = low; j < high; j++) {
            if (data[j] <= pivot) {
                swap(data[j], data[i]);
            }
        }
        swap(data[low], data[high]);
        return i;

    } // Quick Sort Helper

    void displayData(); // Print the current state of the array
    void measureSortTime(void (SortingSystem::*sortFunc)()) {
        clock_t begin = clock();
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        sortFunc();
        cout << "Time spent for sorting system: " << time_spent << endl;
    } // Measure sorting time

    void showMenu() {
        cout << "1. Insertion Sort" << endl;
        cout << "2. Selection Sort" << endl;
        cout << "3. Bubble Sort" << endl;
        cout << "4. Shell Sort" << endl;
        cout << "5. Merge Sort" << endl;
        cout << "6. Quick Sort" << endl;
        cout << "7. Count Sort" << endl;
        cout << "8. Radix Sort" << endl;
        cout << "9. Bucket Sort" << endl;
    } // Display menu for user interaction
};
