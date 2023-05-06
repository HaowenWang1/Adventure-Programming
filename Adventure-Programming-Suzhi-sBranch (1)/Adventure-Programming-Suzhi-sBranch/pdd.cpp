#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
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

            //items.insert(items.begin(), item);
            items.push_back(item);
        }
    }
    else
    {
        std::cout << "Failed to open file:" << filename << endl;
    }
    return items;
}

int MoneyCheck(int Money)
{
   
    if(Money != 1000 && Money != 500 && Money != 200 && Money != 100 && Money != 50 && Money != 20 && Money != 10 && Money != 5)
    {
        cout << "Error :$" << Money/100 << " is not a valid denomination of money. Please try again."<< endl;
        Money = 0;
    }
    else
    {
        Money = Money;
    }

    return Money;
}

void Option_1(LinkedList* stockList)
{
    stockList->PrintItems();
}

void Option_2(LinkedList* stockList, vector<Coin>* coins)
{
    string SearchID;
    Node* SearchedItem = nullptr;
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase:";
    cin >> SearchID;
    while(SearchedItem == nullptr )
    {
        SearchedItem = stockList->get(SearchID);
        if (SearchedItem == nullptr)
        {
            cout << "No this item, try again:";
            cin >> SearchID;
        }
        else
        {
            double NeedMoney;
            int GivenMoney;
            double ChangeMoney;
            bool continueInput = true;
            cout << "You have select";
            cout << "'" << SearchedItem->data->name << SearchedItem->data->description << "'";
            cout << "This will cost you $ " << SearchedItem->data->price.dollars << "." << SearchedItem->data->price.cents << "." << endl;
            NeedMoney = SearchedItem->data->price.dollars*100 + SearchedItem->data->price.cents;
            cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
            cout << "Please enter or ctrl-d on a new line to cancel this purchase:" << endl;
            while( NeedMoney > 0)
            {
                cout << "You still need to give us $" << NeedMoney/100 << ":" ;
                cin >> GivenMoney;
                GivenMoney = MoneyCheck(GivenMoney);
                NeedMoney = NeedMoney - GivenMoney;
                for (Coin& item : *coins)
                {
                    if(item.LoadOne() == GivenMoney)
                    {
                        item.AddCoin();
                    }
                }
            }
            if(NeedMoney < 0)
            {
                ChangeMoney = NeedMoney * -1;
            }
            else
            {
                ChangeMoney = 0;
            }
            
            cout << "Here is your " << SearchedItem->data->name << " and your change of $ " << ChangeMoney/100 << ": ";
        }
    }
}

void Option_6(vector<Coin> coins)
{
    cout << "Coins Summary" << endl;
    cout << "-------------" << endl;
    cout << "Denomination    |    Count" << endl;
    cout << "----------------------------" << endl;
    for (Coin item : coins)
        {
            item.Display();
        }
}
int main(int argc, char **argv)
{
    vector<Stock> items = loadStocks("stock.dat");
    LinkedList stockList;

    for (Stock item : items)
    {
        stockList.addBack(item);
    }
    
    vector<Coin> coins = loadCoin("coins.dat");
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
    cout << "\t9. Abort Program" << endl;
    
    int option = 0;
    while( option != 10)
    {   
        cout << "Select your option (1-9): ";
        cin >> option;
        if(option == 1)
        {
            stockList.PrintItems();
        }
        else if(option == 2)
        {
            Option_2(&stockList , &coins);
        }
        else if(option == 3)
        {
            cout << "option3" << endl;
        }
        else if(option == 4)
        {
            cout << "option4" << endl;
        }
        else if(option == 5)
        {
            cout << "option5" << endl;
        }
        else if(option == 6)
        {
            Option_6(coins);
            // for (Coin item : coins)
            // {
            // item.Display();
            // }
        }
        else if(option == 7)
        {
            cout << "option7" << endl;
        }
        else if(option == 8)
        {
            cout << "option8" << endl;
        }
        else if(option == 9)
        {
            cout << "option9" << endl;
        }
        else if(option == 10)
        {
            cout << "bye" << endl;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << std::endl;
            std::cout << "Please enter 1~9"<< std::endl;
            std::cout << std::endl;
            option = 0;
        }
    }
    
    
    return EXIT_SUCCESS;
}
