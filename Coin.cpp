#include "Coin.h"
#include <string>
 
 // implement functions for managing coins; this may depend on your design.
void Coin::ReduceCoin(){
    this->count = this->count - 1;
}

void Coin::AddCoin(){
    this->count = this->count + 1;
}