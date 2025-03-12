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
    double findMean() {
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += data[i];
        }
        return sum / size;
    }
    T findSummation() {
        T sum = 0;
        for (int i = 0; i < size; i++) {
            sum += data[i];
        }
        return sum;
    }

    // Utility Functions
    void displayArray() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
    }  // Display sorted array
    void inputData() {
        for (int i = 0; i < size; i++) {
            cout << "Enter element " << i+1<<": ";
            cin >> data[i];
        }
        sort();
    }     // Take input dynamically
    void statisticsMenu() {
        int choice;
       do {
           cout << endl;
           cout << "1. Median" << endl;
           cout << "2. Minimum" << endl;
           cout << "3. Maximum" << endl;
           cout << "4. Mean" << endl;
           cout << "5. Summation" << endl;
           cout << "6. Exit" << endl;
           cout << "Enter your choice: ";
           cin >> choice;
           switch (choice) {
               case 1:
                   cout << "Median: " << findMedian()<<endl;
                    break;
               case 2:
                   cout << "Minimum: " << findMin()<<endl;
                   break;
               case 3:
                   cout << "Maximum: " << findMax()<<endl;
                    break;
               case 4:
                   cout << "Mean: " << findMean()<<endl;
                    break;
               case 5:
                   cout << "Summation: " << findSummation()<<endl;
                    break;
               case 6:
                   cout << "Exit...." << endl;
                    break;
           }
       }while (choice != 6);

    }
};
int main() {
    int size;
    cout<<"Enter the number of elements:";
    cin>>size;
    StatisticalCalculation<int> statistics(size);
    statistics.inputData();
    statistics.statisticsMenu();
    return 0;
}

