#include <iostream>
#include "DLinkedList.h"

using namespace std;

int main(int argc, char** argv){
  cout << "starting..." << endl;
  DLinkedList dll;
  dll.insertFront(1);
  dll.insertFront(2);
  dll.insertFront(3);
  dll.insertFront(4);
  dll.insertFront(5);
  dll.insertFront(1);
  dll.insertFront(2);
  dll.insertFront(3);
  dll.insertFront(4);
  dll.insertFront(5);
  dll.printList();
  return 0;
}
