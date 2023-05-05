#include "Coin.h"
#include <iostream>
#include <string>
using namespace std;
 
 // implement functions for managing coins; this may depend on your design.
void Coin::ReduceCoin(){
    this->count = this->count - 1;
}

void Coin::AddCoin(){
    this->count = this->count + 1;
}

int Coin::LoadOne()
{
    return 0;
}

void Coin::Display()
{
    
    if(this->denom == TEN_DOLLARS)
    {
        cout << 1000 << ":" << this->count << endl;
    }
    else if (this->denom == FIVE_DOLLARS)
    {
        cout << 500 << " :" << this->count << endl;
    }
    else if (this->denom == TWO_DOLLARS)
    {
        cout << 200 << " :" << this->count << endl;
    }
    else if (this->denom == ONE_DOLLAR)
    {
        cout << 100 << " :" << this->count << endl;
    }
    else if (this->denom == FIFTY_CENTS)
    {
        cout << 50 << "  :" << this->count << endl;
    }
    else if (this->denom == TWENTY_CENTS)
    {
        cout << 20 << "  :" << this->count << endl;
    }
    else if (this->denom == TEN_CENTS)
    {
        cout << 10 << "  :" << this->count << endl;
    }
    else if (this->denom == FIVE_CENTS)
    {
        cout << 5 << "   :" << this->count << endl;
    }
    
}