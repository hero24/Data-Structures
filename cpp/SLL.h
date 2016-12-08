#include <cstddef>
#include <stdexcept>
#ifndef __IOSTREAM_H
#include <iostream>
#endif
#define __SLL
/*
 * "Idle lawyers tend to become politicians, so there is certain social value in keepig lawyers busy"
 *      ~ A.Silbershatz,J.Peterson - Operating System Concepts.
 */
template <typename T>
struct SLLNode{
    T value;
    struct SLLNode <T>*next;
};
template <class Type>
class SLL{
// Singly Linked List
    public:
        void print(){
            if(isEmpty()){
                std::cout << "[]";
            } else {
                std::cout << "[";
                SLLNode<Type> *element=info.head;
                while (element != NULL){
                    std::cout << element->value << ",";
                    element = element->next;
                }
                std::cout << "]" << std::endl;
            }
        }
        bool contains(Type x){
            SLLNode<Type> *element=info.head;
            while (element != NULL){
                if (element->value == x){
                    return true;
                }
                element = element->value;
            }
            return false;
        }
        bool isEmpty(){
            return (info.head==NULL);
        }
        void add(Type x){
            SLLNode<Type> *node=new SLLNode<Type>;
            node->value=x;
            node->next=NULL;
            if(isEmpty()) info.head=info.tail=node;
            else{
            info.tail->next=node;
            info.tail=node;
            }
            len++;
        }
        SLL& operator --(int n){
            len--;
            if (info.head==info.tail){
                delete info.head;
                info.head=info.tail=NULL;
            } else {
                SLLNode<Type> *temp = info.head;
                while ((temp->next) != info.tail){
                    temp = temp->next;
                }
                info.tail = temp;
                delete temp->next;
                temp->next=NULL;
            }
            return *this;
        }
        Type operator [](int n){
            if (this->len <= n || n < 0) throw std::out_of_range("Index out of range");
            else {
                SLLNode<Type> *temp = info.head;
                while (n > 0){
                    temp = temp->next;
                    n-=1;
                }
                return temp->value;
            }
        }
        void clear(){
            info.head=info.tail=NULL;
            len = 0;
        }
        int length(){
            return len;
        }
        SLL(){
            clear();
        }
        ~SLL(){
            while(!isEmpty()) (*this)--;
        }
    protected:
        struct INFO{
            SLLNode<Type> *head;
            SLLNode<Type> *tail;
        };
        INFO info;
        int len;
};
template <class Type>
class SortedSLL : public SLL<Type> {
// Sorted Singly Linked List
    public:
        void add(Type x){
            SLLNode<Type> *node = new SLLNode<Type>;
            node->value = x;
            if(this->isEmpty()){
                this->info.head=this->info.tail=node;
                node->next=NULL;
            } else {
                SLLNode<Type> *before=NULL, *after=this->info.head;
                enum {FOUND=0,INSEARCH} status=INSEARCH;
                while((status) && (after != NULL)){
                    if (after->value>=x) status=FOUND;
                    else {
                        before=after;
                        after=after->next;
                    }
                } 
                if (before==NULL){
                    this->info.head=node;
                    node->next=after;
                }else if(after==NULL){
                    this->info.tail->next=node;
                    node->next=NULL;
                    this->info.tail=node;
                } else {
                    before->next=node;
                    node->next=after;
                }
            }
            this->len++;
        }
};
