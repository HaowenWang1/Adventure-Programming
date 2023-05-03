#include "LinkedList.h"


LinkedList::LinkedList() {
   head = nullptr;

   // TODO
}

LinkedList::~LinkedList() {
    // TODO
    delete this->head;
    
}

void LinkedList::addBack(Stock data)
{
    Node* newNode = new Node(data, nullptr);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

int LinkedList::size() {
    int count = 0;
    Node* current = head;
    while (current != nullptr)
    {
        ++count;
        current = current->next;
    }
    return count;
}

// Node LinkedList::get(int index){
//     int count = 0;
//     Node* current = head;
//     Node* returnNode;
//     if (index >=0 && index < size())
//     {
//         while(count < index)
//         {
//             ++count;
//             current = current->next;
//         }
//         returnNode = current;
//     }
    
// }