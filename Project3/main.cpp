#include <iostream>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define MAX 10000
int heap[MAX];
int size = 0;
string output[2];

void insert(int arr[],int i);
void remove(int arr[]);
void print(int arr[]);
void heapify(int array[], int n, int i);


int main() {
    int queries;
    cout << "How many Queries will you run?: ";
    cin >> queries;
    cin.ignore();

    for (int i = 0; i < queries; i++) {
        string input;
        getline(cin, input);

        int pos = input.find(" ");
        string function = input.substr(0, pos);
        string number = input.substr(pos + 1);



        if(function == "Insert") {
            int num = stoi(number);
            insert(heap,num);
        }
        else {

        function = input;
        
        if(function == "Delete") {
            remove(heap);
        }
        else if(function == "Print") {
            print(heap);
            i--;
        }
        else {
            cout << "Not a function";
            i--;
        }
        }
    }

    return 0;



}


int parent(int i) {
    return floor((i-1)/2);
}



void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void insert(int heap[],int element) {
    size++;
    heap[size-1] = element;
    heapify(heap, size, size-1);
}

// void buildheap() {
//     int lastNode = (size/2) -1;
//     for(int i = lastNode; i >= 0; i--) {
//         heapify(i);
//     }
// }

void heapify(int heap[],int n, int i)
{
    int largest = i; // Initialize largest as root
    int p = parent(i);
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    if (p >= 0) { 
        if (heap[i] > heap[p]) { 
            swap(heap[i], heap[p]); 
            heapify(heap, n, p); 
        } 
    } 
 
    // If left child is larger than root
    if (l < n && heap[l] > heap[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && heap[r] > heap[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        swap(heap[i], heap[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(heap, n, largest);
    }
}

void remove(int heap[]) {
    
    swap(heap[size-1], heap[0]);
    size--;
    heapify(heap, size, 0);

}

void print(int heap[]) {
    if(size == 0) {
        cout << endl;
        return;
    }
    cout << heap[0] << endl;
}