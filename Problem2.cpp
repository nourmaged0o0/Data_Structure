#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("input.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    int order1, order2, rhs1, rhs2;

    file >> order1 >> rhs1;
    int* poly1 = new int[order1+1];
    for (int i = 0; i <= order1; i++) {
        file >> poly1[i];
    }

    file >> order2 >> rhs2;
    int* poly2 = new int[order2+1];
    for (int i=0; i<= order2; i++) {
        file >> poly2[i];
    }

    file.close();

    int maxO = max(order1, order2);
    int* sum = new int[maxO+1];
    int* diff = new int[maxO+1];


    for (int i=0; i<= maxO; i++) {
        int a = (i <= order1) ? poly1[i] : 0;
        int b = (i <= order2) ? poly2[i] : 0;
        sum[i] = a + b;
        diff[i] = b-a ;
    }


    cout << "First Polynomial: ";
    bool firstTerm = true;
    for (int i=order1 ; i>= 0; i--) {
        if (poly1[i] != 0) {
            if (!firstTerm) cout << " + ";
            cout << poly1[i];
            if (i > 0) cout << "x";
            if (i > 1) cout << "^" << i;
            firstTerm = false;
        }
    }
    cout << "=" << rhs1 << endl;


    cout << "Second Polynomial: ";
    firstTerm = true;
    for (int i=order2; i>= 0; i--) {
        if (poly2[i] != 0) {
            if (!firstTerm) cout << " + ";
            cout << poly2[i];
            if (i > 0) cout << "x";
            if (i > 1) cout << "^" << i;
            firstTerm = false;
        }
    }
    cout << "=" << rhs2 << endl;


    cout << "Sum: ";
    firstTerm = true;
    for (int i=maxO; i>= 0; i--) {
        if (sum[i] != 0) {
            if (!firstTerm) cout << " + ";
            cout << sum[i];
            if (i > 0) cout << "x";
            if (i > 1) cout << "^" << i;
            firstTerm = false;
        }
    }
    cout << "=" << (rhs1 + rhs2) << endl;


    cout << "Difference (Second - First): ";
    firstTerm = true;
    for (int i = maxO; i >= 0; i--) {
        if (diff[i] != 0) {
            if (!firstTerm) cout << " + ";
            cout << diff[i];
            if (i > 0) cout << "x";
            if (i > 1) cout << "^" << i;
            firstTerm = false;
        }
    }
    cout << "=" << (rhs2 - rhs1) << endl;


    delete[] poly1;
    delete[] poly2;
    delete[] sum;
    delete[] diff;

    return 0;
}
