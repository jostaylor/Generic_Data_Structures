#include <iostream>

using namespace std;

template <class T>
class GenQueue{
  public:
    GenQueue(); // constructor
    GenQueue(int mSize); // overload constructor
    ~GenQueue();

    void insert(T data);
    T remove();
    T peek();
    bool isFull();
    bool isEmpty();
    int getSize();

  private:
    int head;
    int tail;
    int maxSize;
    int numElements;
    T* myQueue;
};

// constructor
template <class T>
GenQueue<T>::GenQueue(){
  myQueue = new T[128];
  maxSize = 128;
  numElements = 0;
  head = 0;
  tail = -1;
}

// overload constructor
template <class T>
GenQueue<T>::GenQueue(int mSize){
  myQueue = new T[mSize];
  maxSize = mSize;
  numElements = 0;
  head = 0;
  tail = -1;
}

// destructor
template <class T>
GenQueue<T>::~GenQueue(){
  delete myQueue;
}

// insert method
template <class T>
void GenQueue<T>::insert(T data){
  if (isFull()){
    // creates new array with double the size
    T* newArr = new T[2*maxSize];
    // transfers all information over
    for (int i = 0; i < maxSize; ++i){
      newArr[i] = myQueue[i];
    }
    // takes care of variables
    maxSize *= 2;
    delete myQueue; // only deletes the memory, not the actual variable
    myQueue = newArr;
  }
  // Wraps tail back to the front of the array if its at the last index --> circular queue implementation
  if (tail == (maxSize-1)){
    tail = -1;
  }
  // adds the actual element, finally
  myQueue[++tail] = data;
  ++numElements;
}

// remove method
template <class T>
T GenQueue<T>::remove(){
  T c = myQueue[head++];
  --numElements;
  // Wraps head back to the front of the array --> circular queue implementation
  if (head == maxSize){
    head = 0;
  }
  return c;
}

// peek method
template <class T>
T GenQueue<T>::peek(){
  return myQueue[head];
}

// isFull method
template <class T>
bool GenQueue<T>::isFull(){
  return (numElements == maxSize);
}

// isEmpty method
template <class T>
bool GenQueue<T>::isEmpty(){
  return (numElements == 0);
}

// getSize method
template <class T>
int GenQueue<T>::getSize(){
  return numElements;
}
