#include <iostream>
#include "GenQueue.h"

using namespace std;

int main(int argc, char** argv){
  // object creation on the stack
  GenQueue<char> myQueue(20);

  myQueue.insert('J');
  myQueue.insert('o');
  myQueue.insert('s');
  myQueue.insert('h');
  myQueue.insert('u');
  myQueue.insert('a');

  while(!myQueue.isEmpty()){
    cout << myQueue.remove() << endl;
  }

  // dynamically allocated queue
  GenQueue<char>* myQ = new GenQueue<char>(10); // on the HEAP
  myQ->insert('H'); // arrow dereferences the var and then calls method
  myQ->insert('e');
  myQ->insert('a');
  myQ->insert('p');

  while(!myQ->isEmpty()){
    cout << myQ->remove() << endl;
  }

  // delete allocated memory
  delete myQ;

  return 0;
}
