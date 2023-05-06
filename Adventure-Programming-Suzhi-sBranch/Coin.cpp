#include "Coin.h"
#include <iostream>
#include <string>
#include <iomanip>
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
    if(this->denom == TEN_DOLLARS)
    {
        return 1000;
    }
    else if (this->denom == FIVE_DOLLARS)
    {
        return 500;
    }
    else if (this->denom == TWO_DOLLARS)
    {
        return 200;
    }
    else if (this->denom == ONE_DOLLAR)
    {
        return 100;
    }
    else if (this->denom == FIFTY_CENTS)
    {
        return 50;
    }
    else if (this->denom == TWENTY_CENTS)
    {
        return 20;
    }
    else if (this->denom == TEN_CENTS)
    {
        return 10;
    }
    else if (this->denom == FIVE_CENTS)
    {
        return 5;
    }
    else
    {
        return 0;
    }
}

void Coin::Display()
{
    const int denomination = 16;
    const int Count = 11;
    const char separator = '|';
    if(this->denom == TEN_DOLLARS)
    {
        cout << setw(denomination) << left << "10 Dollar" << separator;
        cout << setw(Count) << right << this->count <<endl;
    }
    else if (this->denom == FIVE_DOLLARS)
    {
        cout << setw(denomination) << left << "5 Dollar" << separator;
        cout << setw(Count) << right << this->count <<endl;
    }
    else if (this->denom == TWO_DOLLARS)
    {
        cout << setw(denomination) << left << "2 Dollar" << separator;
        cout << setw(Count) << right << this->count <<endl;
    }
    else if (this->denom == ONE_DOLLAR)
    {
        cout << setw(denomination) << left << "1 Dollar" << separator;
        cout << setw(Count) << right << this->count <<endl;
    }
    else if (this->denom == FIFTY_CENTS)
    {
        cout << setw(denomination) << left << "50 Cents" << separator;
        cout << setw(Count) << right << this->count <<endl;
    }
    else if (this->denom == TWENTY_CENTS)
    {
        cout << setw(denomination) << left << "20 Cents" << separator;
        cout << setw(Count) << right << this->count <<endl;
    }
    else if (this->denom == TEN_CENTS)
    {
        cout << setw(denomination) << left << "10 Cents" << separator;
        cout << setw(Count) << right << this->count <<endl;
    }
    else if (this->denom == FIVE_CENTS)
    {
        cout << setw(denomination) << left << "5 Cents" << separator;
        cout << setw(Count) << right << this->count <<endl;
    }
    
}