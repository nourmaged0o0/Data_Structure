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
        int temp;
        for (int i = 0; i < size; i++) {
            cout << "Enter element " << i+1<<": ";
            cin >> temp;
            while (!(cin >> temp)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Not a number. Enter element " << i + 1 << ": ";
            }
            data[i] = temp;
        }
        sort();
    }     // Take input dynamically
    void statisticsMenu() {
        string choice;
       while (true) {
           cout << endl;
           cout << "1. Median" << endl;
           cout << "2. Minimum" << endl;
           cout << "3. Maximum" << endl;
           cout << "4. Mean" << endl;
           cout << "5. Summation" << endl;
           cout << "6. Exit" << endl;
           cout<< "Enter your choice (1-5): ";
           cin >> choice;
           if (choice == "1") {

               cout << "Median: " << findMedian()<<endl;
           }
           else if (choice == "2") {
               cout << "Minimum: " << findMin()<<endl;
           }
           else if (choice == "3") {
               cout << "Maximum: " << findMax()<<endl;
           }
           else if (choice == "4") {
               cout << "Mean: " << findMean()<<endl;
           }
           else if (choice == "5") {
               cout << "Summation: " << findSummation()<<endl;
           }
           else if (choice == "6") {
               cout << "Exit..." << endl;
               exit(0);
           }
           else {
               cout << "Wrong choice! Invalid Input" << endl;
           }

       }

    }
};
int main() {
    string choice;
    int num;

    while (true) {
        cout << "Enter the data type: " << endl;
        cout << "1. Integer" << endl;
        cout << "2. Float" << endl;
        cout << "3. String" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        // Clear input stream in case of invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            continue;
        }

        if (choice == "4") {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }

        if (choice != "1" && choice != "2" && choice != "3") {
            cout << "Invalid choice! Please try again." << endl;
            continue;
        }

        cout << "Enter the number of items to sort: ";
        cin >> num;

        // Check for invalid input
        if (cin.fail() || num <= 0) {
            cout << "Invalid input! Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore();
            continue;
        }

        try {
            if (choice == "1") {
                StatisticalCalculation<int> statistics(num);
                statistics.inputData();
                statistics.statisticsMenu();
            }
            // else if (choice == "2") {
            //     SortingSystem<float> sorter(num);
            //     sorter.showMenu();
            // }
            // else if (choice == "3") {
            //     SortingSystem<string> sorter(num);
            //     sorter.showMenu();
            // }
        }
        catch (const exception& e) {
            cout << "An error occurred: " << e.what() << endl;
        }
    }
}

    // StatisticalCalculation<int> statistics(size);
    // statistics.inputData();
    // statistics.statisticsMenu();
