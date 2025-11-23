#include <iostream>
using namespace std;

// Array-based implementation of a Queue
class Queue {
private:
    int* arr;
    int frontIndex, rearIndex, capacity, count;

public:
    Queue(int size) {
        capacity = size;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow!\n";
            return;
        }
        rearIndex = (rearIndex + 1) % capacity; // circular increment
        arr[rearIndex] = value;
        count++;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!\n";
            return;
        }
        frontIndex = (frontIndex + 1) % capacity;
        count--;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return -1;
        }
        return arr[frontIndex];
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue: ";
        for (int i = 0; i < count; i++) {
            int index = (frontIndex + i) % capacity;
            cout << arr[index] << " ";
        }
        cout << endl;
    }
};

// linked list-based implementation of a Queue
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Queue {
private:
    Node* frontNode;
    Node* rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!\n";
            return;
        }
        Node* temp = frontNode;
        frontNode = frontNode->next;
        delete temp;

        if (!frontNode)  // if queue became empty
            rearNode = nullptr;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return -1;
        }
        return frontNode->data;
    }

    bool isEmpty() {
        return frontNode == nullptr;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }
        Node* temp = frontNode;
        cout << "Queue: ";
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};