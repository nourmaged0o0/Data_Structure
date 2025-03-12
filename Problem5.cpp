#include <iostream>
using namespace std;
template <typename T>


class StatisticalCalculation {

private:
    T* data;       // Dynamically allocated array for storing data
    int size;      // Number of elements in the array

public:
    StatisticalCalculation(int size) {
        this->size = size;
        data = new T[size];
    }
    ~StatisticalCalculation() {
        delete[] data;
    }

    void sort() {
    T temp;
        int j;
        for (int i = 1; i < size; i++) {
            temp = data[i];
            j = i - 1;
            while (j >= 0 && data[j] > temp) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = temp;
        }
    }

    // Statistical Calculation Functions
    T findMedian() {
        T median;
        if (size % 2 == 0) { //{1,2,3,5}
            median = (data[((size)/ 2)-1] + data[(size)/ 2])/2;
        }
        else {  //{1,2,3,5,6}
            median = data[((size-1) / 2)];
        }
        return median;
    };
    T findMin() {
        return data[0];
    }
    T findMax() {
        return data[size - 1];
        }
    double findMean();
    T findSummation();

    // Utility Functions
    void displayArray() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
    }  // Display sorted array
    void inputData() {
        for (int i = 0; i < size; i++) {
            cin >> data[i];
        }
        sort();
    }     // Take input dynamically
    void statisticsMenu(); // Menu for statistical operations
};

