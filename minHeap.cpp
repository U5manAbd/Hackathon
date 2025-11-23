#include <iostream>
using namespace std;

class MinHeap {
private:
    int *heap;
    int capacity;
    int size;

    // Get parent, left, right indices (0-indexed)
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    // Heapify DOWN (used after deletion or extractMin)
    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < size && heap[l] < heap[smallest])
            smallest = l;

        if (r < size && heap[r] < heap[smallest])
            smallest = r;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    // Heapify UP (used after insertion)
    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    MinHeap(int cap) {
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
        heap[size++] = key;   // insert at end
        heapifyUp(i);         // bubble up
    }

    // GET MIN (root)
    int getMin() {
        if (size == 0) {
            cout << "Heap empty!\n";
            return -1;
        }
        return heap[0];
    }

    // EXTRACT MIN
    int extractMin() {
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

    // BUILD HEAP from existing array (O(n))
    void buildHeap(int arr[], int n) {
        if (n > capacity) return;

        size = n;
        for (int i = 0; i < n; i++)
            heap[i] = arr[i];

        // start from last non-leaf
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

// heap sort helper: heapify for max-heap
void heapifyMinArr(int arr[], int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] < arr[smallest]) smallest = l;
    if (r < n && arr[r] < arr[smallest]) smallest = r;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapifyMinArr(arr, n, smallest);
    }
}

// Heapsort using min-heap -> descending order
void heapSortDesc(int arr[], int n) {
    // 1) build min heap
    for (int i = n / 2 - 1; i >= 0; --i) heapifyMinArr(arr, n, i);
    // 2) repeatedly swap root(min) with last and heapify reduced heap
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);        // min to its final position (end)
        heapifyMinArr(arr, i, 0);    // heapify reduced heap of size i
    }
}

int main() {
    MinHeap h(20);

    h.insert(10);
    h.insert(5);
    h.insert(20);
    h.insert(3);
    h.insert(8);

    cout << "Min-Heap: ";
    h.print();

    cout << "Min element = " << h.getMin() << endl;

    cout << "Extracted = " << h.extractMin() << endl;
    cout << "After extract: ";
    h.print();

    return 0;
}
