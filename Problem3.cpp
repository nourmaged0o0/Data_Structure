#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = NULL;
    }
};

class SortedLinkedList {
private:
    Node* head;

public:
    SortedLinkedList() {
        head = NULL;
    }

    // Insert an element in sorted order
    void insert(int n) {
        Node* newNode = new Node(n);

        if (head == NULL || head->data >= n) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next != NULL && current->next->data < n) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // Remove element at a given index
    void remove(int index) {
        if (head == NULL) return;

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        for (int i = 0; current->next != NULL && i < index - 1; i++) {
            current = current->next;
        }

        if (current->next == NULL) return;

        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    // Get element at index
    int get(int index) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            if (current == NULL) {
                throw out_of_range("Index out of bounds");
            }
            current = current->next;
        }
        if (current == NULL) {
            throw out_of_range("Index out of bounds");
        }
        return current->data;
    }

    // Destructor to free memory
    ~SortedLinkedList() {
        Node* current = head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Overloaded operator<< for output
    friend ostream& operator<<(ostream& os, const SortedLinkedList& list) {
        Node* current = list.head;
        os << "[";
        while (current != NULL) {
            os << current->data;
            if (current->next != NULL) os << ", ";
            current = current->next;
        }
        os << "]";
        return os;
    }
};

// Test Cases
int main() {
    SortedLinkedList L;

    // Insert elements
    L.insert(5);
    L.insert(8);
    L.insert(7);
    L.insert(6);
    L.insert(6);
    cout << "List after insertions: " << L << endl;  // Expected: [5, 6, 6, 7, 8]

    // Get element at index
    cout << "Element at index 2: " << L.get(2) << endl;  // Expected: 6
    try {
        cout << L.get(10) << endl;  // Should throw exception
    } catch (exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    // Remove elements
    L.remove(0);
    cout << "After removing index 0: " << L << endl;  // Expected: [6, 6, 7, 8]
    
    L.remove(100);  // No change
    cout << "After removing out-of-bounds index: " << L << endl;

    L.remove(2);
    cout << "After removing index 2: " << L << endl;  // Expected: [6, 6, 8]

    L.remove(2);
    cout << "After removing index 2 again: " << L << endl;  // Expected: [6, 6]

    return 0;
}