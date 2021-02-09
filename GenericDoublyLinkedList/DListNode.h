#include <iostream>
#ifndef LISTNODE_H
#define LISTNODE_H

using namespace std;

// List node for single linked list
class ListNode{
  public:
    int data;
    ListNode *next; // pointer to the next node
    ListNode *prev; // pointer to the prev node

    ListNode(); //constructor
    ListNode(int d); // overload constructor
    ~ListNode(); // destructor
};
#endif

ListNode::ListNode(){}

ListNode::ListNode(int d){
  data = d;
  next = NULL; // null pointer
  prev = NULL;
}

ListNode::~ListNode(){
  prev = NULL;
  next = NULL;
}
