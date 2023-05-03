#include "Node.h"

Node::Node(Stock data, Node* next){
    // TODO
    *this->data = data;
    this->next= next;
};
Node::~Node(){
    // TODO
    delete this->data;
    delete this->next;
};