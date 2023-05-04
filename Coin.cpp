#include "Coin.h"
#include <string>
 
 // implement functions for managing coins; this may depend on your design.
void Coin:: ReduceCoin(char type){
    if(this->denom == type)
    {
        this->count = this->count - 1;
    }
}