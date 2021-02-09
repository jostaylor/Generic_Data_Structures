#include <iostream>
#include "TreeNode.h"

using namespace std;

template <class T>
class BST{
  private:
    TreeNode *root;
  public:
    BST();
    ~BST();

    bool search(T* obj);
    void insert(T* obj);
    bool deleteNode(T value);

    // helper functions
    TreeNode* getSuccessor(TreeNode *d);
    bool isEmpty();
    TreeNode* getMin();
    TreeNode* getMax();
    void printTree();
    void recPrint(TreeNode *node); // recursive print
    void recDelete(TreeNode *node);
};

template <class T>
BST<T>::BST(){
  root = NULL;
}

template <class T>
BST<T>::~BST(){
  recDelete(root);
}

template <class T>
void BST<T>::recDelete(TreeNode *node){
  if (node){
    recDelete(node->left);
    recDelete(node->right);
    delete node;
  }
}

template <class T>
void BST<T>::recPrint(TreeNode *node){
  if (node == NULL){
    return;
  }

  recPrint(node->left);
  cout << node->key << endl;
  recPrint(node->right);
}

template <class T>
void BST<T>::printTree(){
  recPrint(root);
}

template <class T>
TreeNode* BST<T>::getMax(){

  TreeNode *curr = root;

  if (root == NULL){
    return NULL;
  }
  while(curr->right != NULL){
    curr = curr->right; // keep going down to the right
  }

  return curr;
}

template <class T>
TreeNode* BST<T>::getMin(){
  TreeNode *curr = root;

  if (root == NULL){
    return NULL;
  }
  while(curr->left != NULL){
    curr = curr->left; // keep going down to the left
  }

  return curr;
}

template <class T>
void BST<T>::insert(T* obj){

  // check if value exists in tree already before proceding
  // every key is unique, so if it is already in the tree, we cannot insert

  TreeNode *node = new TreeNode(obj);
  // int value = node->key; do i need this

  if (root == NULL){ // empty tree
    root = node;
  }
  else{
    // tree is not empty
    // let's find the insertion point
    TreeNode *current = root;
    TreeNode *parent = NULL;

    int deez = 0 ;
    int nuts = 0;
    // traverse tree
    while(deez == nuts){
      parent = current;

      // Compare objects --> for assignment_5, we make comparison operators in the object class itself
      if (obj < current){
        // go left
        current = current->left;

        if (current == NULL){ // found insertion point
          parent->left = node;
          break;
        }
      }
      else{
        // go right
        current = current->right;

        if (current == NULL){ // found the insertion point
          parent->right = node;
          break;
        }
      }
    }
  }
}

// this function may change to return a TreeNode* for assignment_5
template <class T>
bool BST<T>::search(T* obj){

  // if the tree is empty
  if (root == NULL){
    return false;
  }

  // made it here? the tree is for shizzle not empty
  TreeNode *current = root;
  while (current != obj){
    if (obj < current){
      current = current->left;
    }
    else{
      current = current->right;
    }

    if (current == NULL){ //  value not in tree
      return false;
    }
  }
  return true;
}

template <class T>
bool BST<T>::deleteNode(T* obj){

  if (root == NULL) // tree is empty
    return false;

  TreeNode *parent = root;
  TreeNode *current = root;
  bool isLeft = true;

  // let's attempt to find the node to be deleted
  while (current != obj)
  {
    parent = current;

    if (obj < current){
      // go left
      isLeft = true;
      current = current->left;
    }
    else{
      // go right
      isLeft = false;
      current = current->right;
    }

    if (current == NULL){
      // value doesn't exist
      return false;
    }
  }

  // if we make it here, then we have found the node to be deleted

  // if node is external / has 0 children / is a leaf
  if (current->left == NULL && current->right == NULL){

    if (current == root){
      root = NULL;
    }
    else if (isLeft){
      parent->left = NULL;
    }
    else{
      parent->right = NULL;
    }
  }
  // if node has 1 child; and it's a left (no right child)
  else if (current->right == NULL){

    if (current == root){
      root = current->left;
    }
    else if (isLeft){
      parent->left = current->left;
    }
    else{
      parent->right = current->left;
    }
  }
  // if node has 1 child; and it's a right (no left child)
  else if (current->left == NULL){

    if (current == root){
      root = current->right;
    }
    else if (isLeft){
      parent->left = current->right;
    }
    else{
      parent->right = current->right;
    }
  }
  // if the node has 2 children --> uh oh lmao
  // get ready to rumble
  else{

    TreeNode *successor = getSuccessor(current);

    if (current == root){
      root = successor;
    }
    else if (isLeft){
      parent->left = successor;
    }
    else{
      parent->right = successor;
    }

    successor->left = current->left;
  }
  return true;
}

template <class T>
TreeNode* BST<T>::getSuccessor(TreeNode *d){ // d is the node to be deleted
  // the successor can either be the largest number less than d
  // or the smallest number greater than d.
  // Either of these work --> it doesn't matter which route you take --> it's personal preference
  // in this case, we will be choosing the latter --> right once than all the way left
  TreeNode *current = d->right;
  TreeNode *sp = d; // Successor's Parent
  TreeNode *successor = d;

  while(current != NULL){
    sp = successor;
    successor = current;
    current = current->left;
  }
  // we made it here, that means we found our successor
  if (successor != d->right){
    // if our successor is NOT just the node right of our deleted node
    // i.e. the tree is complicated and we have some work to do
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;

}
