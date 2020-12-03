//
// Created by Cheng Stark on 2019-02-13.
//

#include <iostream>
#include <string>
#include <string>
using namespace std;

// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 11.
template <class T>
class Node {
public:
    T value;
    Node<T> *ptr;
};



template <class T>
void print(Node<T> *data, const std::string &label) {
    std::cout << label;
    Node<T> *tmp = data;
    while (tmp != NULL) {
        std::cout << " " << tmp->value;
        tmp = tmp->ptr;
    }
    std::cout << std::endl;
}



template <class T>
void reverse(Node<T>* &input) {

    // FILL IN THIS FUNCTION
    if (input != NULL){
        Node<T>* pos1 = input;
        Node<T>* pos2 = input->ptr;
        Node<T>* tmppos;
        pos1->ptr = NULL;
        while(pos2!=NULL){
            tmppos = pos2->ptr;
            pos2->ptr = pos1;
            pos1 = pos2;
            pos2 = tmppos;
//            print(pos2, "c");
        }
        input = pos1;
    }
}




int main() {

    // manually create a linked list of notes with 4 elements
    Node<int>* my_list = new Node<int>;
    my_list->value = 1;
    my_list->ptr = new Node<int>;
    my_list->ptr->value = 2;
    my_list->ptr->ptr = new Node<int>;
    my_list->ptr->ptr->value = 3;
    my_list->ptr->ptr->ptr = new Node<int>;
    my_list->ptr->ptr->ptr->value = 4;
    my_list->ptr->ptr->ptr->ptr = NULL;


    print(my_list,"my_list before");
    reverse(my_list);
    print(my_list,"my_list after ");


    Node<int>* my_list2 = NULL;


    print(my_list2,"my_list before");
    reverse(my_list2);
    print(my_list2,"my_list after ");


    Node<char>* my_list3 = new Node<char>;
    my_list3->value = 'a';
    my_list3->ptr = new Node<char >;
    my_list3->ptr->value = 'b';
    my_list3->ptr->ptr = NULL;


    print(my_list3,"my_list before");
    reverse(my_list3);
    print(my_list3,"my_list after ");

    Node<string>* my_list4 = new Node<string>;
    my_list4->value = "aaaa";
    my_list4->ptr = NULL;


    print(my_list4,"my_list before");
    reverse(my_list4);
    print(my_list4,"my_list after ");
    // Note: We are not deleting any of the Nodes we created...  so this
    // program has memory leaks!  More on this in lecture 11.

}

// ===========================================================================
