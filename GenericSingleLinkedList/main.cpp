#include <iostream>
#include "SLinkedList.h"

using namespace std;

int main(int argc, char** argv){
  cout << "starting..." << endl;
  SLinkedList sll;
  sll.removeFront();
  sll.insertFront(1);
  sll.insertFront(2);
  sll.insertFront(3);
  sll.insertFront(4);
  sll.insertFront(5);
  sll.insertFront(1);
  sll.insertFront(2);
  sll.insertFront(3);
  sll.insertFront(4);
  sll.insertFront(5);
  return 0;
}
