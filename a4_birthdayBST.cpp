// Kwanghyuk Ryu
// 301475831
// kra69

#include <iostream>
#include "a4_birthdayBST.hpp"
using namespace std;

//use a combination of struct and class
//for simple things like a node we keep it as struct



        BirthdayBSTreeNode* BirthdayBST::insertNode_rec(BirthdayBSTreeNode* node, Birthday* value) {
            if (node == NULL) return newNode(value);
            //continue to either in the left- or right-subtree
            if (node->value > value) node->left = insertNode_rec(node->left, value);
            else node->right = insertNode_rec(node->right, value);
            //returns itself (unchanged)
            return node;
            }
        BirthdayBSTreeNode* BirthdayBST::findMinNode(BirthdayBSTreeNode* node) {
            if (node->left == nullptr) {
                return node;
            }
            else {
                return findMinNode(node->left);
            }
        }
        //internal recursive remove function
        BirthdayBSTreeNode* BirthdayBST::removeNode_rec(BirthdayBSTreeNode* node, Birthday* value) {
            if (node == nullptr) {
                // the value is not found
                return nullptr;
            }
            else if (value->year < node->value->year ||
                    (value->year == node->value->year && value->month < node->value->month) ||
                    (value->year == node->value->year && value->month == node->value->month && value->day < node->value->day)) {
                // the value is in the left subtree
                node->left = removeNode_rec(node->left, value);
                if (node->left != nullptr) {
                    node->left->parent = node;
                }
                return node;
            }
            else if (value->year > node->value->year ||
                    (value->year == node->value->year && value->month > node->value->month) ||
                    (value->year == node->value->year && value->month == node->value->month && value->day > node->value->day)) {
                // the value is in the right subtree
                node->right = removeNode_rec(node->right, value);
                if (node->right != nullptr) {
                    node->right->parent = node;
                }
                return node;
            }
            else {
                // the value is found at this node, so remove it
                if (node->left == nullptr) {
                    // if the node has no left child, replace it with its right child
                    BirthdayBSTreeNode* rightChild = node->right;
                    delete node->value;
                    delete node;
                    size--;
                    return rightChild;
                }
                else if (node->right == nullptr) {
                    // if the node has no right child, replace it with its left child
                    BirthdayBSTreeNode* leftChild = node->left;
                    delete node->value;
                    delete node;
                    size--;
                    return leftChild;
                }
                else {
                    // if the node has both left and right children, replace it with the minimum node in the right subtree
                    BirthdayBSTreeNode* minRight = findMinNode(node->right);
                    node->value = minRight->value;
                    node->right = removeNode_rec(node->right, minRight->value);
                    if (node->right != nullptr) {
                        node->right->parent = node;
                    }
                    return node;
                }
            }
        }
        //internal recursive find function for duplicates, useful for insert
        BirthdayBSTreeNode* BirthdayBST::findNodeByYMDN_rec(BirthdayBSTreeNode* node,
                                                    short year, short month, short day,
                                                    string name) {
            if (node == nullptr) {
                // the value is not found
                return nullptr;
            }
            else if (year < node->value->year ||
                    (year == node->value->year && month < node->value->month) ||
                    (year == node->value->year && month == node->value->month && day < node->value->day)) {
                // the value is in the left subtree
                return findNodeByYMDN_rec(node->left, year, month, day, name);
            }
            else if (year > node->value->year ||
                    (year == node->value->year && month > node->value->month) ||
                    (year == node->value->year && month == node->value->month && day > node->value->day)) {
                // the value is in the right subtree
                return findNodeByYMDN_rec(node->right, year, month, day, name);
            }
            else {
                // the value is found at this node
                if (node->value->name == name) {
                    // the name is the same, so return this node
                    return node;
                }
                else {
                    // the name is different, so keep searching in the right subtree
                    return findNodeByYMDN_rec(node->right, year, month, day, name);
                }
            }
        }
        //internal recursive find function for same month and day, useful for remove
        BirthdayBSTreeNode* BirthdayBST::findNodeByMD_rec(BirthdayBSTreeNode* node, short month, short day) {
            if (node == nullptr) {
                return nullptr; // node not found
            } else if (node->value->month == month && node->value->day == day) {
                return node; // node with matching month and day found
            } else if (node->value->month < month || (node->value->month == month && node->value->day < day)) {
                return findNodeByMD_rec(node->right, month, day); // continue search in right subtree
            } else {
                return findNodeByMD_rec(node->left, month, day); // continue search in left subtree
            }
        }
        //internal recursive print function with matching month and day
        void BirthdayBST::printAllNodeWithMatchingMD_rec(BirthdayBSTreeNode* node, ostream& os,
                                                 short month, short day) {
            if (node == nullptr) {
                return;
            }
            if (node->value->month == month && node->value->day == day) {
                os << node->value->name << " - " << node->value->knownFor << endl;
            }
            printAllNodeWithMatchingMD_rec(node->left, os, month, day);
            printAllNodeWithMatchingMD_rec(node->right, os, month, day);
        }
        //internal recursive print function performing an in-order traversal
        void BirthdayBST::inOrderPrint_rec(BirthdayBSTreeNode* node, ostream& os) {
            if (node != nullptr) {
                inOrderPrint_rec(node->left, os);
                os << node->value->year << "-" << node->value->month << "-" << node->value->day << endl << node->value->name << endl << node->value->knownFor << endl <<"========================================="<<endl;
                inOrderPrint_rec(node->right, os);
            }
        }
        //internal recursive delete function releasing memory use by the tree
        //also releases the Birthday structs along the way
        void BirthdayBST::deleteTree_rec(BirthdayBSTreeNode* node) {
            if (node != nullptr) {
                deleteTree_rec(node->left);
                deleteTree_rec(node->right);
                delete node->value; // free the memory of the Birthday struct
                delete node; // free the memory of the node
            }
        }
        //internal helper function for creating a new tree node
        
        BirthdayBSTreeNode* BirthdayBST::newNode(Birthday* value) {
            BirthdayBSTreeNode* node = new BirthdayBSTreeNode;
            node->value = value;
            node->left = NULL;
            node->right = NULL;
            node->parent = NULL;
            return node;
            }
        //internal helper function for finding the minimal successor, used by remove
        BirthdayBSTreeNode* BirthdayBST::minSuccessor(BirthdayBSTreeNode* node) {
            BirthdayBSTreeNode* current = node;
            while (current->left != NULL) {
                current = current->left;
            }
            return current;
        }

        //constructor
        BirthdayBST::BirthdayBST(){
            root = nullptr;
            size = 0;
        }
        //return the size of the tree
        int BirthdayBST::getSize(){
            return size;
        }
        //insert the Birthday entry to the tree
        void BirthdayBST::insertNode(Birthday* value){
            root = insertNode_rec(root, value);
        }
        //remove a node with matching content from the tree, return the data
        Birthday* BirthdayBST::removeNode(Birthday* value){
            return removeNode_rec(root,value)->value;
        }
        //find a node with matching year, month, day, and name, return the data
        Birthday* BirthdayBST::findNodeByYMDN(short year, short month, short day,
                                string name){
                                    return findNodeByYMDN_rec(root,year,month,day,name)->value;
                                }
        //find a matching node with month and date, return the data
         Birthday* BirthdayBST::findNodeByMD(short month, short day){
            return findNodeByMD_rec(root,month,day)->value;
        }
        //print all content with matching node with month and day
        void BirthdayBST::printAllNodeWithMatchingMD(short month, short day, ostream& os){
            printAllNodeWithMatchingMD_rec(root, os, month, day);
        }
        //performs an in-order traversal and print the content to the output stream
        void BirthdayBST::inOrderPrint(ostream& os){
            inOrderPrint_rec(root, os);
        }
        //destructor
        BirthdayBST::~BirthdayBST(){
            deleteTree_rec(root);
            root = nullptr;
            size = 0;
        }


