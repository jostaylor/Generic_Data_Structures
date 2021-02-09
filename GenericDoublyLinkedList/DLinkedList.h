#include <iostream>
#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include "DListNode.h"

using namespace std;

// Single linked list
class DLinkedList{
  private:
    ListNode *back;
    ListNode *front;
    unsigned int size; // unsigned --> can't be negative --> makes sense here
  public:
    DLinkedList(); // constructor
    ~DLinkedList(); // destructor

    void insertFront(int d);
    void insertBack(int d);
    int removeFront();
    int removeBack();
    int deletePos(int pos);
    int find(int d);
    ListNode* remove(int d);

    // helper functions
    bool isEmpty();
    void printList();
    unsigned int getSize();
};
#endif

DLinkedList::DLinkedList(){
  size = 0;
  front = NULL; // nullptr
  back = NULL;
}

DLinkedList::~DLinkedList(){
  // iterates through the list, nulls out the pointers, and deletes the nodes
  ListNode *current = front;
  while (current != NULL){
    ListNode *next = current->next;
    delete current;
    current = next;
  }
}

unsigned int DLinkedList::getSize(){
  return size;
}

void DLinkedList::printList(){
  ListNode *current = front;
  while (current != NULL)
  {
    cout << current->data << endl;
    current = current->next;
  }
}

void DLinkedList::insertFront(int d){
  ListNode *node = new ListNode(d);
  if (isEmpty()){
    // we have an empty list
    back = node;
  }
  else{
    // not an empty list
    front->prev = node;
    node->next = front;
  }
  front = node;
  size++;
}

void DLinkedList::insertBack(int d){
  ListNode *node = new ListNode(d);
  if (isEmpty()){ // an empty list
    front = node;
  }
  else{ // not an empty list
    back->next = node;
    node->prev = back;
  }
  back = node;
  size++;
}

int DLinkedList::removeFront(){
  ListNode *old = front;
  // nothing you can do if its empty
  if (isEmpty()){
    // throw list empty exception
    return 1; // <-- this works
    // don't wanna use exit(1) because that will terminate your program
  }
  // if there is only one node in the linked list
  if (front == back){
    back = NULL;
  }
  else{
    front->next->prev = NULL;
  }

  front = front->next;
  old->next = NULL;
  int temp = old->data;
  delete old;
  size--;

  return temp;
}

int DLinkedList::removeBack(){

}

ListNode* DLinkedList::remove(int d){ // the actual value/element
  if (isEmpty()){
    // empty list
    // cant do this
  }
  ListNode* curr = front;
  while (curr->data != d){
    // Looking for the value key in the linked list to be removed
    curr = curr->next;

    if (curr == NULL){
      return NULL; // returns null because the value we are looking for is not in this list
    }
  }
  // we found the value in the list to be removed
  if (curr == front){
    // node to be removed is front
    front = curr->next;
  }
  else if (curr == back){
    // node to be removed is back
    back = curr->prev;
  }
  else{
    // node is not the front node --> somewhere in the middle
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }
  // Sets current's pointers to NULL (removes connection from list)
  curr->next = NULL;
  curr->prev = NULL;
  size--;
  return curr;
}

int DLinkedList::deletePos(int pos){

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

int DLinkedList::find(int d){
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

bool DLinkedList::isEmpty(){
  if (size == 0){
    return true;
  }
  else{
    return false;
  }
}
