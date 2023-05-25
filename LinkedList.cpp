#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


LinkedList::LinkedList() {
   head = nullptr;
   count = 0;
   // TODO
}

LinkedList::~LinkedList() {
    // TODO
    Node* current = head;
    while(current != nullptr)
    {
        Node* to_delete = current;
        current = current->next;
        delete to_delete;
    }
    
}

void LinkedList::addBack(Stock data)
{
    Stock* newData = new Stock(data);
    Node* newNode = new Node(newData, nullptr);
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
    count++;
}

bool LinkedList::checkItem(string ID)
{
    bool HaveIt = false;
    Node* current = head;
    while (current != nullptr)
    {
        if(current->data->id == ID)
        {
            HaveIt = true;
        }
        current = current->next;
    }
    return HaveIt;
}
void LinkedList::PrintItems()
{
    const int idWidth = 5;
    const int nameWidth = 40;
    const int availavleWidth = 11;
    const int priceWidth = 0;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID   |Name                                    | Available | Price" << endl;
    cout << "------------------------------------------------------------" << endl;
    Node* current = head;
    while (current != nullptr) {
        cout << setw(idWidth) << left << current->data->id << "|";
        cout << setw(nameWidth) << left << current->data->name << "|";
        cout << setw(availavleWidth) << left << current->data->on_hand << "|";
        cout << setw(priceWidth) << left << current->data->price.dollars << "." << fixed << setprecision(2) << current->data->price.cents << endl;

        current = current->next;
    }
}
void LinkedList::deleteLinkedList() {
    while (head != nullptr) {
        Node* current = head;
        head = head->next;
        current = nullptr;
        delete current;
        count--;
    }
}

int LinkedList::size() {
   
    return count;
}

Node* LinkedList::get(string ID)
{
    Node* current = head;
    Node* returnNode = nullptr;
    while (current != nullptr)
    {
        if(ID == current->data->id && current->data->on_hand > 0)
        {
            returnNode = current;
        }
        current = current->next;
    }
    return returnNode;
}

void LinkedList::removeItem(string ID)
{
    Node* currentNode = head;
    Node* previousNode = nullptr;   

    while (currentNode != nullptr && currentNode->data->id != ID) {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
<<<<<<< HEAD

    if (currentNode != nullptr) {
        
        if (previousNode != nullptr) {
            previousNode->next = currentNode->next;
        }
        
        else {
            head = currentNode->next;
        }

        cout << "The item has been delete." << endl;
    }
}
=======
    //in beginning
    if (previousNode == nullptr)
    {
        head = head->next;
        
    }
    //in middle
    else if (currentNode != nullptr)
    {
        previousNode->next = currentNode->next;
        
    }
    //in end
    else{
        currentNode = previousNode;
        previousNode->next = nullptr;
    }
    currentNode = nullptr;
    delete currentNode;
    cout << "The item has been deleted." << endl;
    count--;
    // if (currentNode != nullptr) {
    //     if (previousNode != nullptr) {
    //         previousNode->next = currentNode->next;
    //     } else {
    //         head = currentNode->next;
    //     }
    //     delete currentNode;
    //     count--;
    //     cout << count <<endl;

    //     cout << "The item has been deleted." << endl;
    // }
}
>>>>>>> Suzhi'sBranch
