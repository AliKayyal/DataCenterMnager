//
// Created by Lian Gh on 03/12/2019.
//

#ifndef HW1_LIST_H
#define HW1_LIST_H




#include <clocale>

template <typename T,typename K>
class ListNode{
public:
    T data;
    K key;
    ListNode<T,K>* next;
    ListNode<T,K>* prev;

    ListNode() {
        next=NULL;
        prev=NULL;

    }
    ListNode(T data,K key,ListNode* next = NULL,ListNode* prev = NULL):
            data(data),key(key),next(next) ,prev(prev){}
    ~ListNode() = default;
};

template<class T,class K>
class List {

public:
    ListNode<T,K>* head;
    ListNode<T,K>* tail;
    int listSize;
    List() : head(NULL), tail(NULL) ,listSize(0){}

    ///copy constructor


    ~List(){
        ListNode<T,K>* iterator = this->head;
        ListNode<T,K>* nextIt;
        while (iterator != NULL){
            nextIt = iterator->next;
            delete iterator;
            iterator = nextIt;
        }
    }

    ListNode<T,K>* AddNode(T& data,K& key){
        ListNode<T,K>* tmp = this->head;
        ListNode<T,K>* newnode = new ListNode<T,K>(data,key);
        if(head==NULL){
            newnode->next=NULL;
            newnode->prev=NULL;
            head=newnode;
            tail=newnode; ///added
        }
        else {
            this->head = newnode;
            newnode->prev = NULL;
            newnode->next = tmp;
            tmp->prev = newnode;
        }
        this->listSize++;
        return newnode;
    }


    int getListSize() const {
        return listSize;
    }


    void DeleteByNode(ListNode<T,K>* node){
        if(node==NULL){
            return;
        }
        if(head==node){
            ///added to update tail - if there is one node (the head) and we want to delete it
            if(this->getListSize()==1){
                tail= nullptr;
            }
            ///
            head=node->next;
            if(head!=NULL) {
                head->prev = NULL;
            }
            delete node;
            listSize --;
            return;
        }
        ListNode<T,K>* tmp=node->next;
        ///added to update tail
        if(tmp== nullptr){
            tail=node->prev;
        }
        ///
        node->prev->next=tmp;
        if(tmp!=NULL) {
            tmp->prev = node->prev;
        }
        listSize --;
        delete node;
    }

    ListNode<T,K>* AddToLast(T& data,K& key){
        ListNode<T,K>* newnode = new ListNode<T,K>(data,key);
        if (tail== nullptr){
            head=newnode;
            newnode->next= nullptr;
            newnode->prev= nullptr;
        }
        else{
            tail->next=newnode;
            newnode->prev=tail;
            newnode->next= nullptr;
            tail=newnode;

        }
        return newnode;
    }


};

#endif //HW1_LIST_H