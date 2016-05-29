#include <cstddef>
#ifndef __IOSTREAM_H
#include <iostream>
#endif
template <typename T>
struct SLLNode{
    T value;
    struct SLLNode <T>*next;
};
template <class Type>
class SLL{
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
        }
        SLL& operator --(Type){
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
            return (*this);
        }
        void clear(){
            info.head=info.tail=NULL;
        }
        SLL(){
            clear();
        }
        ~SLL(){
            while(!isEmpty()) (*this)--;
        }
    private:
        struct INFO{
            SLLNode<Type> *head;
            SLLNode<Type> *tail;
        };
        INFO info;
};