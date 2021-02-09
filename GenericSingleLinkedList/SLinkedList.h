#include <iostream>
#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H
#include "SListNode.h"

using namespace std;

// Single linked list
class SLinkedList{
  private:
    ListNode *front;
    unsigned int size; // unsigned --> can't be negative --> makes sense here
  public:
    SLinkedList(); // constructor
    ~SLinkedList(); // destructor

    void insertFront(int d);
    int removeFront();
    int deletePos(int pos);
    int find(int d);

    // helper functions
    bool isEmpty();
    void printList();
    unsigned int getSize();
};
#endif

SLinkedList::SLinkedList(){
  size = 0;
  front = NULL; // nullptr
}

SLinkedList::~SLinkedList(){
  // iterates through the list, nulls out the pointers, and deletes the nodes
  ListNode *current = front;
  while (current != NULL){
    ListNode* next = current->next;
    delete current;
    cout << "node deleted; size now: " << --size << endl;
    current = next;
  }
  cout << "donzo" << endl;
}

unsigned int SLinkedList::getSize(){
  return size;
}

void SLinkedList::printList(){
  ListNode *current = front;
  while (current != NULL)
  {
    cout << current->data << endl;
    current = current->next;
  }
}

void SLinkedList::insertFront(int d){
  ListNode *node = new ListNode(d);
  node->next = front;
  front = node;
  size++;
}

int SLinkedList::removeFront(){
  // checks for empty list
  if (isEmpty()){
    cout << "Error! Linked list is empty, cannot remove node." << endl;
    exit(1);
    //throw "Error! List is empty, cannot remove node.";
  }
  int tmp = front->data;
  ListNode *old = front;
  front = front->next;
  old->next = NULL; // just to be safe
  delete old;
  size--;

  return tmp;
}

int SLinkedList::deletePos(int pos){

  int idx = 0;
  ListNode *prev = front;
  ListNode *curr = front;

  while (idx != pos){
    prev = curr; // stays behind current
    curr = curr->next;
    idx++;
  }
  // Make sure to add checks for valid pos and curr != nullptr

  prev->next = curr->next;
  curr->next = NULL; // null out the one you're deleting
  int temp = curr->data;
  delete curr;
  size--;
  return temp;
}

int SLinkedList::find(int d){
  int idx = 0;
  ListNode *curr = front;
  while (curr != NULL){
    if (curr->data == d){
      break;
    }
    idx++;
    curr = curr->next;
  }

  if (curr == NULL){
    idx = -1;
  }
  return idx;
}

bool SLinkedList::isEmpty(){
  if (size == 0){
    return true;
  }
  else{
    return false;
  }
}
