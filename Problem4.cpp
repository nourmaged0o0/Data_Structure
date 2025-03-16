#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

template<typename T>
class SortingSystem {
private:
    T *data;
    int size;

public:
    SortingSystem(int n) {
        this->data = new T[n];
        this->size = n;
    }

    ~SortingSystem() {
        delete[] this->data;
    }

    void insertionSort() {
        for (int i = 1; i < size; i++) {
            T temp = data[i];
            int j = i - 1;
            while (j >= 0 && temp < data[j]) {
                data[j + 1] = data[j];
                j = j - 1;
            }
            data[j + 1] = temp;
        }
    }

    void selectionSort() {
        cout << "Sorting using Selection Sort..." << endl;
        cout << "Initial Data: ";
        displayData();

        for (int i = 0; i < size - 1; i++) {
            int minIndx = i;
            for (int j = i + 1; j < size; j++) {
                if (data[j] < data[minIndx]) {
                    minIndx = j;
                }
            }
            if (minIndx != i) {
                swap(data[i], data[minIndx]);
            }
            cout << "Iteration " << (i + 1) << ": ";
            displayData();
        }
    }

    void bubbleSort() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    void shellSort() {
        for (int interval = size / 2; interval > 0; interval /= 2) {
            for (int i = interval; i < size; i++) {
                T temp = data[i];
                int j;
                for (j = i; j >= interval && data[j - interval] > temp; j -= interval) {
                    data[j] = data[j - interval];
                }
                data[j] = temp;
            }
        }
    }

    void merge(int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        T *L = new T[n1], *R = new T[n2];
        for (int i = 0; i < n1; i++) L[i] = data[left + i];
        for (int j = 0; j < n2; j++) R[j] = data[mid + 1 + j];
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) data[k++] = L[i++];
            else data[k++] = R[j++];
        }
        while (i < n1) data[k++] = L[i++];
        while (j < n2) data[k++] = R[j++];
        delete[] L;
        delete[] R;
    }

    void mergeSort(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(left, mid);
            mergeSort(mid + 1, right);
            merge(left, mid, right);
        }
    }

    int partition(int low, int high) {
        T pivot = data[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (data[j] < pivot) {
                i++;
                swap(data[i], data[j]);
            }
        }
        swap(data[i + 1], data[high]);
        return i + 1;
    }

    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

    void countSort() {
        // Find the maximum element
        T maxVal = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > maxVal) {
                maxVal = data[i];
            }
        }

        // Create a count array
        int *count = new int[maxVal + 1];
        for (int i = 0; i <= maxVal; i++) {
            count[i] = 0;
        }

        // Store count of each element
        for (int i = 0; i < size; i++) {
            count[data[i]]++;
        }

        // Update the array
        int index = 0;
        for (int i = 0; i <= maxVal; i++) {
            while (count[i] > 0) {
                data[index++] = i;
                count[i]--;
            }
        }

        delete[] count;
    }

    void radixSort() {
        // Find the maximum number to know number of digits
        T max = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > max) {
                max = data[i];
            }
        }

        // Do counting sort for every digit
        for (int exp = 1; max / exp > 0; exp *= 10) {
            // Create count array and output array
            T *output = new T[size];
            int count[10] = {0};

            // Store count of occurrences in count[]
            for (int i = 0; i < size; i++) {
                count[(data[i] / exp) % 10]++;
            }

            // Change count[i] so that count[i] now contains actual
            // position of this digit in output[]
            for (int i = 1; i < 10; i++) {
                count[i] += count[i - 1];
            }

            // Build the output array
            for (int i = size - 1; i >= 0; i--) {
                output[count[(data[i] / exp) % 10] - 1] = data[i];
                count[(data[i] / exp) % 10]--;
            }

            // Copy the output array to data[]
            for (int i = 0; i < size; i++) {
                data[i] = output[i];
            }

            delete[] output;
        }
    }

    void bucketSort() {
        // Find the maximum and minimum values
        T max_val = data[0];
        T min_val = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > max_val) max_val = data[i];
            if (data[i] < min_val) min_val = data[i];
        }

        // Calculate the range of values
        T range = max_val - min_val + 1;

        // Create n buckets
        int num_buckets = size;
        T **buckets = new T*[num_buckets];
        int *bucket_sizes = new int[num_buckets];

        // Initialize buckets
        for (int i = 0; i < num_buckets; i++) {
            buckets[i] = new T[size];  // Allocate maximum possible size
            bucket_sizes[i] = 0;       // Initialize bucket sizes to 0
        }

        // Put array elements into buckets
        for (int i = 0; i < size; i++) {
            int bucket_index = (data[i] - min_val) * (num_buckets - 1) / range;
            buckets[bucket_index][bucket_sizes[bucket_index]++] = data[i];
        }

        // Sort individual buckets using insertion sort
        for (int i = 0; i < num_buckets; i++) {
            for (int j = 1; j < bucket_sizes[i]; j++) {
                T temp = buckets[i][j];
                int k = j - 1;
                while (k >= 0 && buckets[i][k] > temp) {
                    buckets[i][k + 1] = buckets[i][k];
                    k--;
                }
                buckets[i][k + 1] = temp;
            }
        }

        // Concatenate all buckets back into the original array
        int index = 0;
        for (int i = 0; i < num_buckets; i++) {
            for (int j = 0; j < bucket_sizes[i]; j++) {
                data[index++] = buckets[i][j];
            }
            delete[] buckets[i];
        }

        delete[] buckets;
        delete[] bucket_sizes;
    }

    // Print the current state of the array
    void displayData() {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    // Measure sorting time for any sorting algorithm
    double measureSortTime(void (SortingSystem<T>::*sortFunc)()) {
        auto start = chrono::high_resolution_clock::now();
        (this->*sortFunc)();
        auto end = chrono::high_resolution_clock::now();

        // Calculate duration in seconds
        chrono::duration<double> duration = end - start;
        return duration.count();
    }

    double measureSortTime(void (SortingSystem<T>::*sortFunc)(int, int), int param1, int param2) {
        auto start = chrono::high_resolution_clock::now();
        (this->*sortFunc)(param1, param2);
        auto end = chrono::high_resolution_clock::now();

        // Calculate duration in seconds
        chrono::duration<double> duration = end - start;
        return duration.count();
    }

    // Display menu for user interaction
    void showMenu() {
        char continueOption = 'y';

        while (continueOption == 'y' || continueOption == 'Y') {
            cout << "Select a sorting algorithm:\n";
            cout << "1. Insertion Sort\n2. Selection Sort\n3. Bubble Sort\n4. Shell Sort\n5. Merge Sort\n6. Quick Sort\n7. Count Sort (Only for integers)\n8. Radix Sort (Only for integers)\n9. Bucket Sort\nEnter your choice (1-9): ";
            int choice;
            cin >> choice;
            if (choice < 1 || choice > 9) {
                cout << "Invalid choice! Try again." << endl;
                continue;
            }

            // Get data from user
            cout << "Enter " << size << " elements:" << endl;
            for (int i = 0; i < size; i++) {
                cout << "Enter data " << (i + 1) << ": ";
                cin >> data[i];
            }

            double sortTime = 0.0;

            switch (choice) {
                case 1:
                    sortTime = measureSortTime(&SortingSystem<T>::insertionSort);
                    break;
                case 2:
                    sortTime = measureSortTime(&SortingSystem<T>::selectionSort);
                    break;
                case 3:
                    sortTime = measureSortTime(&SortingSystem<T>::bubbleSort);
                    break;
                case 4:
                    sortTime = measureSortTime(&SortingSystem<T>::shellSort);
                    break;
                case 5:
                    sortTime = measureSortTime(&SortingSystem<T>::mergeSort, 0, size - 1);
                    break;
                case 6:
                    sortTime = measureSortTime(&SortingSystem<T>::quickSort, 0, size - 1);
                    break;
                case 7:
                    sortTime = measureSortTime(&SortingSystem<T>::countSort);
                    break;
                case 8:
                    sortTime = measureSortTime(&SortingSystem<T>::radixSort);
                    break;
                case 9:
                    sortTime = measureSortTime(&SortingSystem<T>::bucketSort);
                    break;
            }

            cout << "Sorted Data: ";
            displayData();
            cout << "Sorting Time: " << fixed << sortTime << " seconds" << endl;

            cout << "Do you want to sort another dataset? (y/n): ";
            cin >> continueOption;
        }

        cout << "Thank you for using the sorting system! Goodbye!" << endl;
    }
};

int main() {
    int num;
    cout << "Enter the number of items to sort: ";
    cin >> num;
    if (num <= 0) {
        cout << "Invalid input! Exiting." << endl;
        return 1;
    }

    SortingSystem<int> sorter(num);
    sorter.showMenu();

    return 0;
}