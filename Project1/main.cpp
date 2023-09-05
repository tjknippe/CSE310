#include <iostream>
#include <stdio.h>
using namespace std;

void bubbleSort(int elements, int array[]);

int main() {
    int elements;
    cin >> elements;
    cin.ignore();
    int array[elements];
    for(int i = 0; i < elements;i++) {
        cin >> array[i];
    }
    bubbleSort(elements, array);
    
    for(int i = 0; i < elements; i++) {
        cout<< array[i] << " ";
    }
    

    
    return 0;
}

void bubbleSort(int elements, int array[]) {
    for(int i = 0; i < elements*2; i++) {
        for(int j = 0; j < elements-1; j++) {
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }

        }
        
    }
}