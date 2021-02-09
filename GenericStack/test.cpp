#include <iostream>
#include "GenStack.h"

using namespace std;

int main2(int argc, char** agrv){

  cout << "this is some text" << endl;
  for (int i = 0; i < 50; ++i){
    if (i % 2 == 0){
      cout << "i is even. i = " << i << endl;
    }
    else{
      cout << "i is odd. i = " << i << endl;
    }
  }
  cout << "some friggin brackets [][][][]" << endl;


  // ---------------- testing the stack -------------
  cout << "hello stack" << endl;

  GenStack<char> myStack(1);

  myStack.push('J');
  myStack.push('o');
  myStack.push('s');
  myStack.push('h');

  cout << "popping: " << myStack.pop() << endl;
  cout << "Peek-a-boo: " << myStack.peek() << endl;

  myStack.push('F');
  cout << "peek-a-boo: " << myStack.peek() << endl;

  while(!myStack.isEmpty()){
    cout << "popping: " << myStack.pop() << endl;
  }

  cout << "is stack[]] empty? " << myStack.isEmpty() << endl;
  //cout << myStack.pop() << endl;

  GenStack<int>* stack2 = new GenStack<int>(20);

  stack2->push(3);
  stack2->push(69);
  cout << "peeking: " << stack2->peek() << endl;

  stack2->push(43);

  while (!stack2->isEmpty()){
    cout << "popping:" << stack2->pop() << endl;
  }

  delete stack2;
  //------------------------------------------------------

}
