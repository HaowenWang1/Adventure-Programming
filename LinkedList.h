#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <string>
using namespace std;

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...
    void addBack(Stock data);

    // Node get(int index);

    int size();

    Node* get(string ID);

    void PrintItems();

    void removeItem(string ID);

    bool checkItem(string ID);

    Node* GetHead() const{
    return head;
}
private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


