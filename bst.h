/*
    Header file for BST.
    I have declared class for BSTNode straight away as it was simple.
    While I have declared class and then defined methods using "::" for bST.
*/

#pragma once
#ifndef BST_H
#define BST_H

#include <iostream>

template <typename T>
class BSTNode {
public:
//kept these public as it would be a lot tough to modify them using getters and setters.
	T item; 
	BSTNode<T>* left;
    BSTNode<T>* right;

    BSTNode(T val){
        this->item = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    BSTNode(T val,BSTNode<T>* l ,BSTNode<T>* r ){
        this->item = val;
        this->left = l;
        this->right = r;
    }
    
};

//BST class template declaration.
template <typename T>
class BST{
    private:
        BSTNode<T>* root;
        int size;
        T* arr;
    public:
        BST();
        BST(T rootData);
        ~BST();
        BSTNode<T>* Insert(T item);
        BSTNode<T>* Insert(T newItem,BSTNode<T>* node); //auxiliary function for recursive part.
    
        //A simple utility function for inorder traversal.
        void Inorder();
        void Inorder(BSTNode<T>* node);//auxiliary function for recursive part.

        //Gets the minimum value node. The right most node.
        BSTNode<T>* minValueNode(BSTNode<T>* node);
        
        void Remove(T item); 
        BSTNode<T>* Remove(BSTNode<T>* root, T item); //auxiliary function for recursive part.
        
        bool ElementExists(T item);
        bool ElementExists(BSTNode<T>* node,T item);//auxiliary function for recursive part.
        
        BSTNode<T>* Find(T item);
        BSTNode<T>* Find(BSTNode<T>* node,T item); //auxiliary function for recursive part.
        
        T* toArray(); //Returns a dynamically allocated 1-D array with inorder traversal of BST.
        void storeInOrder(BSTNode<T>* node,int* indexptr); //stores the array inOrder fashion.
        
        void Empty(); //Empties the tree.
        void Empty(BSTNode<T>* node);

        int Length();
};


//constructor.
template <typename T>
BST<T>::BST(){
    this->root = nullptr;
    this->size = 0;
}

//parameterised constructor.
template <typename T>
BST<T>::BST(T rootData){
this->root->item = new BSTNode<T>(rootData);
this->size = 0;
}

//destructor.
template <typename T>
BST<T>::~BST(){
    delete[] arr; //deletes the Array of BST.
    this->Empty(); //empties or deletes tree recursively. Along with all the allocated objects.
}


//Inserts the element as per conditions.
template <typename T>
BSTNode<T>* BST<T>::Insert(T item){

if(root==nullptr)
    {
        this->root = new BSTNode<T>(item);
        this->size++;
       return root;
    }
else
    {
        this->size++;
        return Insert(item, root);
    }
}

//recursive aux function.
template <typename T>
BSTNode<T>* BST<T>::Insert(T newItem,BSTNode<T>* node){

if(newItem <node->item)
    {
        if(node->left == nullptr)
        {
            node->left = new BSTNode<T>(newItem);
            return node->left;
        }
        else
            Insert(newItem , node->left);
    }
else //assuming no duplicates. so else case will be >
    {
        if(node->right == nullptr)
            {node->right = new BSTNode<T>(newItem);
            return node->right;
            }
        else
            Insert(newItem , node->right);
    }

return NULL;
}

//Inorder Traversal.
template <typename T>
void BST<T>::Inorder(){
    Inorder(this->root);
}

//Inorder Traversal's recursive part.
template <typename T>
void BST<T>::Inorder(BSTNode<T>* node)
{
    if (node != nullptr) {
        Inorder(node->left);
        std::cout << node->item<<" ";
        Inorder(node->right);
    }
}

//gets min value node .
template <typename T>
BSTNode<T>* BST<T>::minValueNode(BSTNode<T>* node){
BSTNode<T>* current = node;

if(current == nullptr)
    return nullptr;

while(current->left != nullptr){
    current = current->left;
}
return current;
}

//Removes the item.
template <typename T>
void BST<T>::Remove(T item)
{
this->root = Remove(this->root,item);
this->size--;
}

//Recursive aux method, for above remove method. 
template <typename T>
BSTNode<T>* BST<T>::Remove(BSTNode<T>* node, T item)
{
    // base case
    if (node == nullptr)
        return node;
 
    /* If the item to be deleted is
     smaller than the node's
     item, then it lies in left subtree
     */

    if (item < node->item)
        node->left = Remove(node->left, item);
 
    /* If the item to be deleted is
     greater than the node's
     item, then it lies in right subtree
    */
    else if (item > node->item)
        node->right = Remove(node->right, item);
 
    /* if item is same as node's item, then This is the node
     to be deleted */
    else {
        // node has no child
        if (node->left==nullptr and node->right==nullptr)
            return nullptr;
       
        // node with only one child or no child
        else if (node->left == nullptr) {
            BSTNode<T>* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            BSTNode<T>* temp = node->left;
            delete node;
            return temp;
        }
 
        /* node with two children: Get the inorder successor
         (smallest in the right subtree) */
        BSTNode<T>* temp = minValueNode(node->right);
 
        // Copy the inorder successor's content to this node
        node->item = temp->item;
 
        // Delete the inorder successor
        node->right = Remove(node->right, temp->item);
    }
    return node;
}

//Checks whether an element exists or not.
template <typename T>
bool BST<T>::ElementExists(T item){
return ElementExists(this->root , item);
}

template <typename T>
bool BST<T>::ElementExists(BSTNode<T>* node,T item)
{
if(node == nullptr)
    return false;

if (node->item == item)
    return true;

if (ElementExists(node->left,item))
    return true;

return ElementExists(node->right,item);
}


//Finds a node and returns a pointer to it if it exists otherwise returns nullptr.
template <typename T>
BSTNode<T>* BST<T>::Find(T item){
return Find(this->root, item);
}
//recursive part for find.
template <typename T>
BSTNode<T>* BST<T>::Find(BSTNode<T>* node,T item){

if(node == nullptr)
    return nullptr;

if (node->item == item)
    return node;

BSTNode<T>* temp = Find(node->left,item);

if (temp == nullptr)
    return Find(node->right,item);
}
        
//Returns the length or size of bst.
//another way would be to go recursively . I thought of doing this.
template <typename T>
int BST<T>::Length(){
    return this->size;
}

//toArray() that returns an Inorder traversal of BST in array form. 
template <typename T>
T* BST<T>::toArray()
{
arr = new T[this->size];
int index=0;
int* indexptr = &index;
storeInOrder(this->root,indexptr);
return arr;
}

// Utility function for toArray().
template <typename T>
void  BST<T>::storeInOrder(BSTNode<T>* node,int* indexptr)
{
	if(node == nullptr) 
		return; 
	
    storeInOrder(node->left,indexptr); 
	
    this->arr[*indexptr] = node->item ; 
    *indexptr = *indexptr + 1;
	
    storeInOrder(node->right,indexptr); 
}

//Empties the BST.
template <typename T>
void  BST<T>::Empty(){
    Empty(this->root);
    this->size = 0;
    this->root = nullptr;
}

//recursive part.
template <typename T>
void  BST<T>::Empty(BSTNode<T>* node){
if (node == nullptr)
    return;

Empty(node->left);
Empty(node->right);

delete node;
}

#endif