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
        for (int i = 1; i < size; i++) {
            T temp = data[i];
            int j = i - 1;
            while (j >= 0 && temp < data[j]) {
                data[j + 1] = data[j];
                j = j - 1;
            }
            data[j + 1] = temp;
        }
    } // (1) Insertion Sort
    void selectionSort() {
        int n = size;
        for (int i = 0; i < n - 1; i++) {
            int minIndx = i;
            for (int j = i + 1; j < n; j++) {
                if (data[j] < data[minIndx]) {
                    minIndx = j;
                }
            }
            if (minIndx != i) {
                swap(data[i], data[minIndx]);
            }
        }
    } // (2) Selection Sort
    void bubbleSort() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    } // (3) Bubble Sort
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
    } // (4) Shell Sort
    void mergeSort(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(left, mid);
            mergeSort(mid + 1, right);
            merge(left, mid, right);
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

        int maxVal = data[0];
        int minVal = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > maxVal) maxVal = data[i];
            if (data[i] < minVal) minVal = data[i];
        }

        int range = maxVal - minVal + 1;
        int* count = new int[range]{0};
        for (int i = 0; i < size; i++) {
            count[data[i] - minVal]++;
        }
        int index = 0;
        for (int i = 0; i < range; i++) {
            while (count[i]-- > 0) {
                data[index++] = i + minVal;
            }
        }
        delete[] count;



    } // (7) Count Sort (Only for int)
    void radixSort() {
        int maxVal = data[0];
        for (int i = 1; i < size; i++)
            if (data[i] > maxVal) maxVal = data[i];

        for (int place = 1; maxVal / place > 0; place *= 10)
            countSort(place);
    } // (8) Radix Sort (Only for int)
    void bucketSort() {
        if (size <= 0) return;

        int bucketCount = size;
        T maxVal = data[0], minVal = data[0];

        for (int i = 1; i < size; i++) {
            if (data[i] > maxVal) maxVal = data[i];
            if (data[i] < minVal) minVal = data[i];
        }

        T range = maxVal - minVal + 1;

        T** buckets = new T*[bucketCount];
        int* bucketSizes = new int[bucketCount]();

        for (int i = 0; i < bucketCount; i++) {
            buckets[i] = new T[size];
        }

        for (int i = 0; i < size; i++) {
            int index = (bucketCount * (data[i] - minVal)) / range;
            if (index >= bucketCount) index = bucketCount - 1;
            buckets[index][bucketSizes[index]++] = data[i];
        }

        for (int i = 0; i < bucketCount; i++) {
            sort(buckets[i], buckets[i] + bucketSizes[i]);
        }

        int index = 0;
        for (int i = 0; i < bucketCount; i++) {
            for (int j = 0; j < bucketSizes[i]; j++) {
                data[index++] = buckets[i][j];
            }
            delete[] buckets[i];
        }

        delete[] buckets;
        delete[] bucketSizes;
    } // (9) Bucket Sort

    void merge(int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        T *L = new T[n1], *R = new T[n2];

        int i, j, k;
        for (i = 0; i < n1; i++)
            L[i] = data[left + i];
        for (j = 0; j < n2; j++)
            R[j] = data[mid + 1 + j];

        i = j = 0;
        k = left;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                data[k] = L[i];
                i++;
            } else {
                data[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            data[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            data[k] = R[j];
            j++;
            k++;
        }
        delete[] L;
        delete[] R;
    } // Merge Sort Helper
    int partition(int low, int high) {
        int pivot = data[low];
        int i = low;
        for (int j = low+1; j < high; j++) {
            if (data[j] <= pivot) {
                swap(data[j], data[i]);
            }
        }
        swap(data[low], data[high]);
        return i;

    } // Quick Sort Helper

    void displayData() {
        cout << "Current Data: ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    } // Print the current state of the dataay
    void measureSortTime(void (SortingSystem::*sortFunc)()) {
        clock_t begin = clock();
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
(this->*sortFunc)();
        cout << "Time spent for sorting system: " << time_spent << endl;
    } // Measure sorting time

    void showMenu() {

        while (true){


            cin.ignore();  // Clear the input buffer before getline()

            // Initialize SortingSystem for strings

            cout << endl;

            // Step 2: User Enters Data to Sort

            for (int i = 0; i < size; ++i) {
                T element;
                cout << "Enter data " << (i + 1) << ": ";
                cin >> element;
                data[i] = element;
                cout << endl;
            }

            cout << endl;

            displayData();


            cout << "1. Insertion Sort" << endl;
            cout << "2. Selection Sort" << endl;
            cout << "3. Bubble Sort" << endl;
            cout << "4. Shell Sort" << endl;
            cout << "5. Merge Sort" << endl;
            cout << "6. Quick Sort" << endl;
            cout << "7. Count Sort (Only for integers)" << endl;
            cout << "8. Radix Sort (Only for integers)" << endl;
            cout << "9. Bucket Sort" << endl;
            cout <<"10. Exit" << endl;
            cout << "Enter your choice (1-10): ";

            string choice;
            cin >> choice;

            if (choice == "1") {
                measureSortTime(&SortingSystem::insertionSort);
            } else if (choice == "2") {
                measureSortTime(&SortingSystem::selectionSort);
            } else if (choice == "3") {
                measureSortTime(&SortingSystem::bubbleSort);
            } else if (choice == "4") {
                measureSortTime(&SortingSystem::shellSort);
            } else if (choice == "5") {
                clock_t begin = clock();
                mergeSort(0, size - 1);
                clock_t end = clock();
                double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                cout << "Time spent for merge sort: " << time_spent << endl;
            } else if (choice == "6") {
                clock_t begin = clock();
                quickSort(0, size - 1);
                clock_t end = clock();
                double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                cout << "Time spent for quick sort: " << time_spent << endl;
            } else if (choice == "7") {
                measureSortTime(&SortingSystem::countSort);
            } else if (choice == "8") {
                measureSortTime(&SortingSystem::radixSort);
            } else if (choice == "9") {
                measureSortTime(&SortingSystem::bucketSort);
            } else if (choice == "10") {
                exit(0);
            } else {
                cout << "Invalid choice! Please try again." << endl;
            }

        }
    }
};

void menu1() {
    int num;

    cout << "Enter the number of items to sort: ";
    cin >> num;


    SortingSystem<string> sort(num);
    sort.showMenu();


}

int main() {
   menu1();
return 0;
}





// there is an error i cant fix it idk why
// make the validation part of integer
