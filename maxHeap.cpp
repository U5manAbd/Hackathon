#include <iostream>
using namespace std;

class MaxHeap {
private:
    int *heap;
    int capacity;
    int size;

    // Parent and children (0-indexed)
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    // Heapify DOWN → used after delete or extractMax
    void heapifyDown(int i) {
        int largest = i;
        int l = left(i);
        int r = right(i);

        if (l < size && heap[l] > heap[largest])
            largest = l;

        if (r < size && heap[r] > heap[largest])
            largest = r;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

    // Heapify UP → used after insert
    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    MaxHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new int[cap];
    }

    // INSERT
    void insert(int key) {
        if (size == capacity) {
            cout << "Heap full!\n";
            return;
        }

        int i = size;
        heap[size++] = key;  // insert at end
        heapifyUp(i);        // bubble up
    }

    // GET MAX
    int getMax() {
        if (size == 0) {
            cout << "Heap empty!\n";
            return -1;
        }
        return heap[0];
    }

    // EXTRACT MAX
    int extractMax() {
        if (size == 0) {
            cout << "Heap empty!\n";
            return -1;
        }

        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;

        heapifyDown(0);
        return root;
    }

    // BUILD MAX HEAP from array (O(n))
    void buildHeap(int arr[], int n) {
        if (n > capacity) return;

        size = n;
        for (int i = 0; i < n; i++)
            heap[i] = arr[i];

        // heapify from last non-leaf node
        for (int i = (n/2) - 1; i >= 0; i--)
            heapifyDown(i);
    }

    // DISPLAY
    void print() {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << "\n";
    }
};

// heap sort helper: heapify max in array
void heapifyMaxArr(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyMaxArr(arr, n, largest);
    }
}

// Standard heapsort using max-heap -> ascending order
void heapSortAsc(int arr[], int n) {
    // 1) build max heap
    for (int i = n / 2 - 1; i >= 0; --i) heapifyMaxArr(arr, n, i);
    // 2) repeatedly swap root with last and heapify reduced heap
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);        // max to its final position
        heapifyMaxArr(arr, i, 0);    // heapify reduced heap of size i
    }
}


int main() {
    MaxHeap h(20);

    h.insert(10);
    h.insert(50);
    h.insert(20);
    h.insert(3);
    h.insert(8);

    cout << "Max-Heap: ";
    h.print();

    cout << "Max element = " << h.getMax() << endl;

    cout << "Extracted = " << h.extractMax() << endl;
    cout << "After extract: ";
    h.print();
    return 0;
}
