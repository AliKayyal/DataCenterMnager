//
// Created by Lian Gh on 03/12/2019.
//

#ifndef HW1_AVLTREE_H
#define HW1_AVLTREE_H

#include <new>
#include "AvlNode.h"
#include "library1.h"
template <typename T,typename S>
class AVLTree{
public:
    AvlNode<T,S>* head;
    int tree_size;
    typedef enum {
        LL,RR,LR,RL,NR
    } RotationType;


    AVLTree(AvlNode<T,S>* head= NULL,int size=0):head(head),tree_size(size){}
    ~AVLTree(){
        destroyTree(head);
    }

    int getSize(){
        return tree_size;
    }

    void destroyTree(AvlNode<T,S>* head){
        if(!head){
            return;
        }
        destroyTree(head->right);
        destroyTree(head->left);
        delete head;
    }

    RotationType typeOfRotation(AvlNode<T,S>* node){
        int bf=node->getBalanceFactor();
        if(bf==2){
            int lbf=(node->left)->getBalanceFactor();
            if(lbf>=0){
                return LL;
            }
            if(lbf==-1){
                return LR;
            }
        }
        if(bf==-2){
            int rbf=(node->right)->getBalanceFactor();
            if(rbf<=0){
                return RR;
            }
            if(rbf==1){
                return RL;
            }
        }
        return NR;
    }

    void balanceTree(AvlNode<T,S>* ptr){
        while(ptr!= NULL){
            ptr->setHeight();
            RotationType rotationType=typeOfRotation(ptr);
            if(rotationType==LL){
                ptr=LLRotation(ptr);
            }
            else if(rotationType==RR){
                ptr=RRRotation(ptr);
            }
            else if(rotationType==RL){
                ptr=RLRotation(ptr);
            }
            else if(rotationType==LR){
                ptr=LRRotation(ptr);
            }
            ptr=ptr->parent;
        }
    }

    void insert(T& data,S& key){
        if(find(key)!= NULL){
            return;
        }
        AvlNode<T, S> *newNode;
        try {
            newNode = new AvlNode<T, S>(key, data);
        }
        catch (std::bad_alloc&){
            throw std::bad_alloc();
        }
        if(!head){
            head=newNode;
            tree_size++;
            return;
        }
        AvlNode<T,S>* current=head;
        AvlNode<T,S>* last= current;
        while(current!= NULL){
            last=current;
            if(current->key > newNode->key){
                current=current->left;
            }
            else{
                current=current->right;
            }
        }
        newNode->parent=last;
        if(last->key > newNode->key){
            last->left=newNode;
        }
        else{
            last->right=newNode;
        }
        tree_size++;
        balanceTree(last);
    }

    void removeByKey(S key){
        AvlNode<T,S>* node_to_remove=find(key);
        if(!node_to_remove){
            return;
        }
        removeNodeFromTree(node_to_remove);
    }

    void removeLeaf(AvlNode<T,S>* node_to_delete,AvlNode<T,S>* parent){
        if(node_to_delete==head){
            this->head= NULL;
        }
        else{
            parent->updateSon(node_to_delete, NULL);
        }
    }

    void removeOneChild(AvlNode<T,S>* node_to_delete,AvlNode<T,S>* parent){
        if(head!=node_to_delete){
            if(node_to_delete->left!= NULL){
                parent->updateSon(node_to_delete,node_to_delete->left);
            }
            else{
                parent->updateSon(node_to_delete,node_to_delete->right);
            }
        }
        else{
            if(node_to_delete->left!= NULL){
                head=node_to_delete->left;
                head->parent= NULL;
            }
            else{
                head=node_to_delete->right;
                head->parent= NULL;
            }
        }
    }
    void removeNodeFromTree(AvlNode<T,S>* node_to_delete){
        if(!node_to_delete){
            return;
        }
        tree_size--;
        AvlNode<T,S>* parent=node_to_delete->parent;
        int children_num=node_to_delete->numOfChildren();
        if(node_to_delete->isLeaf()){
            removeLeaf(node_to_delete,parent);
        }
        if(children_num==1){
            removeOneChild(node_to_delete,parent);
        }
        if(children_num==2){
            AvlNode<T,S>* nextV=node_to_delete;
            nextV=nextV->right;
            while(nextV->left){
                nextV=nextV->left;
            }
            swapNodes(node_to_delete,nextV);
            int vChildNum=node_to_delete->numOfChildren();
            parent=node_to_delete->parent;
            if(vChildNum==1){
                removeOneChild(node_to_delete,parent);
            }
            else{
                removeLeaf(node_to_delete,parent);
            }
        }
        delete node_to_delete;
        balanceTree(parent);
    }

    void swapNodes(AvlNode<T,S>* node1,AvlNode<T,S>* node2){
        if(!node1||!node2){
            return;
        }
        AvlNode<T,S>* parent1=node1->parent;
        AvlNode<T,S>* parent2=node2->parent;
        int tmp_height=node1->height;
        node1->height=node2->height;
        node2->height=tmp_height;

        if(parent1!= NULL){
            parent1->updateSon(node1,node2);
        }
        else{
            node2->parent= NULL;
            head=node2;
        }
        parent2->updateSon(node2,node1);
        node1->right->parent=node2;
        node1->left->parent=node2;
        node2->left=node1->left;
        AvlNode<T,S>* tmp=node2->right;
        node2->right=node1->right;
        node1->left= NULL;
        node1->right=tmp;
        if(tmp!= NULL){
            tmp->parent=node1;
        }

    }

    AvlNode<T,S>* find(S key){
        return recursiveFind(key,head);
    }
    AvlNode<T,S>* recursiveFind(S& key,AvlNode<T,S>* node){
        if(!node){
            return NULL;
        }
        if(node->key==key){
            return node;
        }
        if(node->key>key){
            return recursiveFind(key,node->left);
        }
        else{
            return recursiveFind(key,node->right);
        }
    }



    AvlNode<T,S>* RRRotation(AvlNode<T,S>* B){

        if(B== NULL){
            return NULL;
        }
        AvlNode<T,S>* A=B->right;
        if(A->left!= NULL){
            A->left->parent=B;
        }
        AvlNode<T,S>* tmp_parent = B->parent;
        B->right=A->left;
        A->parent=tmp_parent;
        B->parent=A;
        A->left=B;
        if(A->parent){
            if(A->parent->right==B){
                A->parent->right=A;
            }
            else{
                A->parent->left=A;
            }
        }
        if(tmp_parent != NULL){
            if (tmp_parent->right == B) {
                tmp_parent->right=A;
            }
            if (tmp_parent->left == B) {
                tmp_parent->left=A;
            }
        }
        if(head == B){
            head = A;
        }
        B->setHeight();
        A->setHeight();
        return A;
    }

    AvlNode<T,S>* LLRotation(AvlNode<T,S>* B){
        AvlNode<T,S>* A=B->left;
        if(A->right){
            A->right->parent=B;
        }
        AvlNode<T,S>* tmp_parent = B->parent;
        B->left=A->right;
        A->parent=tmp_parent;
        B->parent=A;
        A->right=B;
        if(A->parent){
            if(A->parent->right==B){
                A->parent->right=A;
            }
            else{
                A->parent->left=A;
            }
        }
        if(tmp_parent != NULL){
            if (tmp_parent->right == B) {
                tmp_parent->right=A;
            }
            if (tmp_parent->left == B) {
                tmp_parent->left=A;
            }
        }
        if(head == B){
            head = A;
        }
        B->setHeight();
        A->setHeight();
        return A;
    }


    AvlNode<T,S>* LRRotation(AvlNode<T,S>* C){
        AvlNode<T,S>* A=C->left;
        C->left=RRRotation(A);
        return LLRotation(C);
    }


    AvlNode<T,S>* RLRotation(AvlNode<T,S>* C){
        AvlNode<T,S>* A=C->right;
        C->right=LLRotation(A);
        return RRRotation(C);
    }

};



#endif
