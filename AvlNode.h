//
// Created by Lian Gh on 03/12/2019.
//

#ifndef HW1_AVLNODE_H
#define HW1_AVLNODE_H
//#include "exceptions.h"
#include <clocale>
template<class T,class S>
class AVLTree;

template <typename T,typename S>
class AvlNode{
public:
    S key;
    T data;
    AvlNode* left;
    AvlNode* right;
    AvlNode* parent;
    int height;

    AvlNode(S& key,T& data, AvlNode *left= NULL, AvlNode *right= NULL, AvlNode *parent= NULL):
            key(key),data(data), left(left), right(right),
              parent(parent), height(0) {}

    ~AvlNode(){
        delete data;
    }

    void setHeight() {
        int r_height, l_height;
        if (left == NULL) {
            l_height = -1;
        } else {
            l_height = left->height;
        }
        if (right == NULL) {
            r_height = -1;
        } else {
            r_height = right->height;
        }
        height = (r_height > l_height ? r_height : l_height)+1;
    }

    int getBalanceFactor(){
        int r_height, l_height;
        if (left == NULL) {
            l_height = -1;
        } else {
            l_height = left->height;
        }
        if (right == NULL) {
            r_height = -1;
        } else {
            r_height = right->height;
        }
        return l_height-r_height;
    }


    bool isLeaf(){
        return height==0;
    }


    int numOfChildren(){
        int c=0;
        if(right!= NULL){
            c++;
        }
        if(left!= NULL){
            c++;
        }
        return c;
    }

    void updateSon(AvlNode<T,S>* old_son,AvlNode<T,S>* new_son){
        if(old_son== NULL){
            return;
        }
        if(this->left==old_son){
            left=new_son;
        }

        if(this->right==old_son){
            right=new_son;
        }
        if(new_son!= NULL){
            new_son->parent=this;
        }
    }
};

#endif //HW1_AVLNODE_H
