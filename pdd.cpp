#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "LinkedList.h"
using namespace std;

vector<Stock> loadStocks(string filename)
{
    //create a vector to hold data
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
    //create a vector to hold coin data
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

            items.insert(items.begin(), item);
            //items.push_back(item);
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
   //check if the input money is valable
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
    //print the items
    stockList->PrintItems();
}

void Option_2(LinkedList* stockList, vector<Coin>* coins)
{
    //search a item
    string SearchID;
    Node* SearchedItem = nullptr;
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase:";
    cin >> SearchID;
    //check if the item is in list
    while(SearchedItem == nullptr )
    {
        SearchedItem = stockList->get(SearchID);
        if (SearchedItem == nullptr)
        {
            cout << "No this item, or the item is sale out, try again:";
            cin >> SearchID;
        }
        else
        {
            double NeedMoney;
            int GivenMoney;
            double ChangeMoney;
            bool continueInput = true;
            std::vector<double> change_coins;
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
                //check if the money if valble
                GivenMoney = MoneyCheck(GivenMoney);
                NeedMoney = NeedMoney - GivenMoney;
                //add money to list depend on user's input
                for (Coin& item : *coins)
                {
                    if(item.LoadOne() == GivenMoney)
                    {
                        item.AddCoin();
                    }
                }
            }
            ChangeMoney = -NeedMoney;
            while (ChangeMoney > 0)
            {
                bool coin_found = false;
                for (int i = coins->size() - 1; i >= 0; i--)
                {
                    Coin& item = coins->at(i);
                    if (item.LoadOne() <= ChangeMoney && item.count > 0)
                    {
                        ChangeMoney = ChangeMoney - item.LoadOne();
                        item.ReduceCoin();
                        coin_found = true;
                        change_coins.push_back(item.LoadOne());
                        
                    }
                }
                if (!coin_found)
                {
                    std::cout << "Unable to find coins to make change!" << std::endl;
                    
                }
            }
            cout << "Here is your " << SearchedItem->data->name << " and your change of $ " << -NeedMoney/100 << ": ";
            for (double coin : change_coins)
            {   
                if (coin>=100)
                {
                    std::cout << coin/100 << " dollars,";
                }else
                {
                    std::cout << coin << " cents,";
                }
            }
            SearchedItem->data->on_hand = SearchedItem->data->on_hand - 1;
        }
    }
}

void Option_3(const string& filename, LinkedList&  LinkedList)
{
    ofstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cout << "cannot open the file: "<< filename << endl;
        return;
    }

    Node* currentNode = LinkedList.GetHead();
    while (currentNode != nullptr)
    {
        Stock* stock = currentNode->data;
        ostringstream priceStream;
        priceStream << fixed;
        priceStream.precision(2);
        priceStream << stock->price.dollars << "." << setw(2) << setfill('0') << stock->price.cents;
        string line = stock->id + "|" + stock->name + "|" + stock->description + "|" + priceStream.str() + "|" + to_string(stock->on_hand) + "\n";
        file.write(line.c_str(), line.size());
        currentNode = currentNode->next;
    }
    cout << "Created the file " << filename << " for new stock list" <<endl;
    file.close();
    LinkedList.~LinkedList();
}

void Option_5(LinkedList *LinkedList)
{
    cout << "Which item you want to remove: ";
    string id;
    cin >> id;
    Node* currItem = nullptr;
    while (currItem == nullptr)
    {
        currItem = LinkedList->get(id);
        if (currItem == nullptr)
        {
            cout << "We don't have this item. Please try agian: ";
            cin >> id;
        }
    }
    LinkedList->removeItem(id);
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

vector<Stock> loadStocks(string filename)
{
    //create a vector to hold data
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
    //create a vector to hold coin data
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

            items.insert(items.begin(), item);
            //items.push_back(item);
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
   //check if the input money is valable
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
    //print the items
    stockList->PrintItems();
}

void Option_2(LinkedList* stockList, vector<Coin>* coins)
{
    //search a item
    string SearchID;
    Node* SearchedItem = nullptr;
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase:";
    cin >> SearchID;
    //check if the item is in list
    while(SearchedItem == nullptr )
    {
        SearchedItem = stockList->get(SearchID);
        if (SearchedItem == nullptr)
        {
            cout << "No this item, or the item is sale out, try again:";
            cin >> SearchID;
        }
        else
        {
            double NeedMoney;
            int GivenMoney;
            double ChangeMoney;
            bool continueInput = true;
            std::vector<double> change_coins;
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
                //check if the money if valble
                GivenMoney = MoneyCheck(GivenMoney);
                NeedMoney = NeedMoney - GivenMoney;
                //add money to list depend on user's input
                for (Coin& item : *coins)
                {
                    if(item.LoadOne() == GivenMoney)
                    {
                        item.AddCoin();
                    }
                }
            }
            ChangeMoney = -NeedMoney;
            while (ChangeMoney > 0)
            {
                bool coin_found = false;
                for (int i = coins->size() - 1; i >= 0; i--)
                {
                    Coin& item = coins->at(i);
                    if (item.LoadOne() <= ChangeMoney && item.count > 0)
                    {
                        ChangeMoney = ChangeMoney - item.LoadOne();
                        item.ReduceCoin();
                        coin_found = true;
                        change_coins.push_back(item.LoadOne());
                        
                    }
                }
                if (!coin_found)
                {
                    std::cout << "Unable to find coins to make change!" << std::endl;
                    
                }
            }
            cout << "Here is your " << SearchedItem->data->name << " and your change of $ " << -NeedMoney/100 << ": ";
            for (double coin : change_coins)
            {   
                if (coin>=100)
                {
                    std::cout << coin/100 << " dollars,";
                }else
                {
                    std::cout << coin << " cents,";
                }
            }
            SearchedItem->data->on_hand = SearchedItem->data->on_hand - 1;
        }
    }
}

void Option_3(const string& filename, LinkedList&  LinkedList)
{
    ofstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cout << "cannot open the file: "<< filename << endl;
        return;
    }

    Node* currentNode = LinkedList.GetHead();
    while (currentNode != nullptr)
    {
        Stock* stock = currentNode->data;
        ostringstream priceStream;
        priceStream << fixed;
        priceStream.precision(2);
        priceStream << stock->price.dollars << "." << setw(2) << setfill('0') << stock->price.cents;
        string line = stock->id + "|" + stock->name + "|" + stock->description + "|" + priceStream.str() + "|" + to_string(stock->on_hand) + "\n";
        file.write(line.c_str(), line.size());
        currentNode = currentNode->next;
    }
    cout << "Created the file " << filename << " for new stock list" <<endl;
    file.close();
    LinkedList.~LinkedList();
}

void Option_5(LinkedList *LinkedList)
{
    cout << "Which item you want to remove: ";
    string id;
    cin >> id;
    Node* currItem;
    currItem = LinkedList->get(id);
    if (currItem == nullptr)
    {
        cout << "We don't have this item. Please try agian: ";
        cin >> id;
    }
    else
    {
        LinkedList->removeItem(id);
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
    //write stokes into items vector
    vector<Stock> items = loadStocks("stock.dat");
    LinkedList stockList;
    //add items to list
    for (Stock item : items)
    {
        stockList.addBack(item);
    }
    
    vector<Coin> coins = loadCoin("coins.dat");
    
    int option = 0;
    while( option != 3)
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
            string filename = "try.dat";
            Option_3(filename, stockList);
        }
        else if(option == 4)
        {
            cout << "option4" << endl;
        }
        else if(option == 5)
        {
            Option_5(&stockList);
        }
        else if(option == 6)
        {
            Option_6(coins);
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
{
    //write stokes into items vector
    vector<Stock> items = loadStocks("stock.dat");
    LinkedList stockList;
    //add items to list
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
    while( option != 3)
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
            string filename = "try.dat";
            Option_3(filename, stockList);
        }
        else if(option == 4)
        {
            cout << "option4" << endl;
        }
        else if(option == 5)
        {
            Option_5(&stockList);
        }
        else if(option == 6)
        {
            Option_6(coins);
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
            return EXIT_SUCCESS;
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
