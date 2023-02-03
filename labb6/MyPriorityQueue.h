
#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
#include <string>


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue() = default;

    ~MyPriorityQueue() = default;

    // Adds an element to the queue
    void push(const T& t);

    // Returns the first element in the queue
    T top()const;

    // Removes the first element in the queue
    void pop();

    // Returns true if the queue is empty
    bool empty()const;

    //Returns the size of the queue
    int size()const;


private:
    // Sifts the heap up (from the given index).
    void bubbleUp(int index);
    // Sifts the heap down (from the given index).
    void bubbleDown(int index);
};

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    bubbleUp(vector_array.size() - 1);
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    T firstElement = vector_array[0];
    vector_array[0] = *vector_array.end();
    vector_array[vector_array.size() - 1] = firstElement;

    vector_array.pop_back();

    bubbleDown(0);
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return size() == 0;
}

template <typename T, typename C>
int MyPriorityQueue<T, C>::size()const {
    return vector_array.size();
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::bubbleUp(int index) {
    int parentIndex = (index - 1) / 2;
    T parent = vector_array[parentIndex];
    T child = vector_array[index];

    if (strictly_larger_operator(parent, child) && index != 0) {
        vector_array[parentIndex] = vector_array[index];
        vector_array[index] = parent;

        bubbleUp(parentIndex);
    }
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::bubbleDown(int index) {
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = leftChildIndex + 1;

    int smallest = index;

    if (leftChildIndex < vector_array.size() && strictly_larger_operator(vector_array[smallest], vector_array[leftChildIndex])) {
        smallest = leftChildIndex;
    }
    if (rightChildIndex < vector_array.size() && strictly_larger_operator(vector_array[smallest], vector_array[rightChildIndex])) {
        smallest = rightChildIndex;
    }

    if (smallest != index) {
        // Swap
        T temp = vector_array[index];
        vector_array[index] = vector_array[smallest];
        vector_array[smallest] = temp;

        bubbleDown(smallest);
    }

}


#endif // MY_PRIORITY_QUEUE_H
