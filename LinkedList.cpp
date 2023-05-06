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