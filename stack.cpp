#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        cout << value << " pushed onto stack." << endl;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! Nothing to pop." << endl;
            return -1;
        }
        int poppedValue = topNode->data;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        cout << poppedValue << " popped from stack." << endl;
        return poppedValue;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return -1;
        }
        return topNode->data;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }

    ~Stack() {
        while (!isEmpty()) pop();
    }
};

int main() {
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top element: " << s.peek() << endl;

    s.pop();
    s.pop();

    cout << "Is stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;

    s.pop();
    s.pop();

    return 0;
}
