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

    ~SortedLinkedList() {
        Node* current = head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

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

int main() {
    SortedLinkedList myList;

    myList.insert(5);
    myList.insert(8);
    myList.insert(7);
    myList.insert(6);
    myList.insert(6);
    cout << "List after insertions: " << myList << endl;  // output: [5, 6, 6, 7, 8]

    cout << "Element at index 2: " << myList.get(2) << endl;  // output: 6
    try {
        cout << myList.get(10) << endl;  // Should Error
    } catch (exception& e) {
        cout << "Exception: " << e.what() << endl;
    }


    myList.remove(0);
    cout << "After removing index 0: " << myList << endl;  // output: [6, 6, 7, 8]
    
    myList.remove(100);  // no change
    cout << "After removing out-of-bounds index: " << myList << endl;

    myList.remove(2);
    cout << "After removing index 2: " << myList << endl;  // output: [6, 6, 8]

    myList.remove(2);
    cout << "After removing index 2 again: " << myList << endl;  // output: [6, 6]

    return 0;
}