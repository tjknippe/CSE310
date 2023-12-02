#include "minheap.h"

MinHeap::MinHeap() {
    keys = nullptr;
    values = nullptr;
    size = 0;
    capacity = 0;

}

void MinHeap::init(int size) {
    MinHeap::capacity = size;
    keys = new double[size];
    values = new int[size];
}

void MinHeap::push(double key, int value) {
    if(size == capacity) {
        return;
    }
    size++;
    keys[size] = key;
    values[size] = value;
    heapifyUp(size);
}

int MinHeap::pop() {
    if(empty()) {
        return -1;
    }
    int root = values[1];
    values[1] = values[size];
    size--;
    heapifyDown(size);
    return root;
}

bool MinHeap::empty() const {
    return (size == 0) ? (true): (false);
}

void MinHeap::heapifyUp(int index) {
    while(index > 1 && keys[index] < keys[index/2]) {
        swap(index, index/2);
        index = index/2;
    }
}

void MinHeap::heapifyDown(int index) {
    if(index == 1) {
        return;
    }
    int smallest = (keys[2*index] < keys[2*index + 1]) ? 2*index:2*index+1;
    if(keys[smallest] < keys[index]) {
        swap(smallest, index);
        index = smallest;
        heapifyDown(index);
    }
}

void MinHeap::swap(int i, int j) {
    double tempkey = keys[i];
    int tempval = values[i];
    keys[i] = keys[j];
    values[i] = values[j];
    keys[j] = tempkey;
    values[j] = tempval;
}