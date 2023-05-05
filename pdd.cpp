#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "LinkedList.h"
using namespace std;

vector<Stock> loadStocks(string filename)
{
    vector<Stock> items;
    ifstream inputfile(filename);

    if(inputfile)
    {
        string line;
        while(getline(inputfile, line))
        {
            Stock item;
            stringstream ss(line);
            string token;
            
            getline(ss, token, '|');
            item.id = token;
            getline(ss, token, '|');
            item.name = token;
            getline(ss, token, '|');
            item.description = token;
            getline(ss, token, '|');
            double price = stod(token);
            item.price.dollars = static_cast<unsigned int>(price);
            item.price.cents = static_cast<unsigned int>((price - item.price.dollars) * 100);
            getline(ss, token);
            item.on_hand = stoi(token);

            items.push_back(item);
        }
    }
    else
    {
        std::cout << "Failed to open file:" << filename << endl;
    }

    return items;
}

vector<Coin> loadCoin(string filename)
{
    vector<Coin> items;
    ifstream inputfile(filename);

    if(inputfile)
    {
        string line;
        while(getline(inputfile, line))
        {
            Coin item;
            int price;
            stringstream ss(line);
            string token;

            getline(ss, token, ',');
            price = stod(token);
            if(price == 1000)
            {
                item.denom = TEN_DOLLARS;
            }
            else if(price == 500)
            {
                item.denom = FIVE_DOLLARS;
            }
            else if(price == 200)
            {
                item.denom = TWO_DOLLARS;
            }
            else if(price == 100)
            {
                item.denom = ONE_DOLLAR;
            }
            else if(price == 50)
            {
                item.denom = FIFTY_CENTS;
            }
            else if(price == 20)
            {
                item.denom = TWENTY_CENTS;
            }
            else if(price == 10)
            {
                item.denom = TEN_CENTS;
            }
            else if(price == 5)
            {
                item.denom = FIVE_CENTS;
            }
            getline(ss,token);
            item.count = stoi(token);

            items.push_back(item);
        }
    }
    else
    {
        std::cout << "Failed to open file:" << filename << endl;
    }
    return items;
}

void Option_1()
{
    
}
int main(int argc, char **argv)
{
    cout << "Main Menu: " << endl;
    cout << "\t1.Display Items" << endl;
    cout << "\t2.Purchase Items" << endl;
    cout << "\t3.Save and Exit" << endl;
    cout << "Adminstrator-Only Menu:" << endl;
    cout << "\t4.Add Item" << endl;
    cout << "\t5.Remove Item" << endl;
    cout << "\t6.Display Coins" << endl;
    cout << "\t7.Reset Stock" << endl;
    cout << "\t8.Reset Coins" << endl;
    cout << "\t9.Abort Program" << endl;
    cout << "Select your option (1-9): ";

    vector<Stock> items = loadStocks("stock.dat");
    LinkedList stockList;

    for (Stock item : items)
    {
        stockList.addBack(item);
    }
    stockList.PrintItems();
    vector<Coin> coins = loadCoin("coins.dat");
    for (Coin item : coins)
    {
        item.Display();
    }

    int option;
    switch (option)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    default:
        break;
    }
    
    return EXIT_SUCCESS;
}
