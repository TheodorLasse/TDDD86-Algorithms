
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{
public:
    // Inits empty vector.
    MyVector();

    // Destructor
    ~MyVector();

    // Copy constructor.
    MyVector(const MyVector& other);

    // Assignement operator.
    MyVector& operator =(const MyVector& other);

    // Pushes an element to the vector.
    void push_back(const T&);

    // Pops the last element from the vector.
    void pop_back();

    // Index operator
    T& operator[](unsigned i);

    // Const index operator
    const T& operator[](unsigned i)const;

    void remove(unsigned i);

    // Returns true if the vector is empty.
    bool empty()const;

    // Returns a pointer to the first element.
    T* begin();

    // Returns a pointer to the last element.
    T* end();

    // Deletes all elements in the vector.
    void clear();

    // Returns the number of elements in the vector.
    unsigned size()const;

private:
    unsigned numerOfElements = 0;
    unsigned capacity = 1;
    // Doubles the size of the storage
    void doubleArraySize();
    // Copies the storage from another vector
    void copy(const MyVector& other);
    T* storage = nullptr;
};

template<typename T>
MyVector<T>::MyVector(){
    storage = new T[1];
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    copy(other);
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if (other != *this) {
        delete[] storage;
        copy(other);
    }

    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if (capacity <= size()) {
        doubleArraySize();
    }

    storage[size()] = e;
    numerOfElements++;

    // O(N)
    /*for (int i = numerOfElements - 1; i >= 0; i--) {
        storage[i] = storage[i];
    }*/
}

template<typename T>
void MyVector<T>::pop_back(){
    if (size() == 0) {
        return;
    }

    numerOfElements--;
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return storage[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return storage[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    return size() == 0;
}

template<typename T>
void MyVector<T>::clear(){
    numerOfElements = 0;
    capacity = 1;
    delete[] storage;
    storage = new T[1];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numerOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    return storage;
}

template<typename T>
T* MyVector<T>::end(){
    return storage + size() - 1;
}

template<typename T>
void MyVector<T>::doubleArraySize(){
    T* newArray = new T[capacity * 2];

    for (unsigned i = 0; i < size(); i++) {
        newArray[i] = storage[i];
    }

    delete[] storage;
    storage = newArray;
    capacity *= 2;
}

template<typename T>
void MyVector<T>::copy(const MyVector &other) {
    storage = new T[other.capacity];
    numerOfElements = other.numerOfElements;
    capacity = other.capacity;

    for (int i = 0; i < other.size(); i++) {
        storage[i] = other.storage[i];
    }
}

#endif // MY_VECTOR_H
