#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "LinkedList.h"
#include "Coin.h"
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

bool compareCoins(const Coin& coin1, const Coin& coin2) {
    return coin1.LoadOne() > coin2.LoadOne();
}

void UpdateCoinFile(const vector<Coin>* coins, const string& coinFile) {
    ofstream file(coinFile);
    if (!file.is_open()) {
        cout << "Failed to open " << coinFile << endl;
        return;
    }

  
    vector<Coin> sortedCoins = *coins;
    sort(sortedCoins.begin(), sortedCoins.end(), compareCoins);

    for (const Coin& coin : sortedCoins) {
        file << coin.LoadOne() << "," << coin.count << endl;
    }

    file.close();

    cout << "Coin file updated." << endl;
}

void Option_2(LinkedList* stockList, vector<Coin>* coins)
{
    //search a item
    string SearchID;
    Node* SearchedItem = nullptr;
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase(you can type 'help' to see what should enter):";
    //check if the item is in list
    while(SearchedItem == nullptr )
    {
        cin >> SearchID;
        SearchedItem = stockList->get(SearchID);
        if (SearchedItem == nullptr && SearchID == "help")
        {
            cout << "In here, you should print a ID of the item you want to buy, like I0001 etc" << endl;
            cout << "Please enter the id of the item you wish to purchase:";
        }
        else if (SearchedItem == nullptr)
        {
            cout << "No this item, or the item is sale out, you can also type 'help' to see what you can do" << endl;
            cout << "try again:" ;
        }
        else
        {
            double NeedMoney;
            int GivenMoney;
            string GivenMoneyInString;
            double ChangeMoney;
            vector<double> change_coins;
            cout << "You have select";
            cout << "'" << SearchedItem->data->name << SearchedItem->data->description << "'";
            cout << "This will cost you $ " << SearchedItem->data->price.dollars << "." << SearchedItem->data->price.cents << "." << endl;
            NeedMoney = SearchedItem->data->price.dollars*100 + SearchedItem->data->price.cents;
            cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
            cout << "Please enter or ctrl-d on a new line to cancel this purchase:" << endl;
            while( NeedMoney > 0)
            {
                cout << "You still need to give us $" << NeedMoney/100 << ":" ;
                cin >> GivenMoneyInString;
                if(GivenMoneyInString == "help")
                {
                    cout << "In here, you should type the money you wan to pay as cents and interger as the unit like 200, 500 etc." << endl;
                }
                else
                {
                    try
                    {
                        GivenMoney = stoi(GivenMoneyInString);
                        //check if the money if valble
                        GivenMoney = MoneyCheck(GivenMoney);
                        NeedMoney = NeedMoney - GivenMoney;
                        //add money to list depend on user's input
                        for (size_t i = 0; i < coins->size(); i++)
                        {
                            Coin& item = (*coins)[i];
                            if (item.LoadOne() == GivenMoney)
                            {
                                item.AddCoin();
                            }
                        }
                    }
                    catch (const invalid_argument &ia)
                    {
                        cerr << "Please inter a interger number like 200, 500 etc. If you do not know how to to, you can type a 'help' to help you." << endl;
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
                    cout << "Unable to find coins to make change!" << endl;
                    
                }
            }
            cout << "Here is your " << SearchedItem->data->name << " and your change of $ " << -NeedMoney/100 << ": ";
            for (size_t i = 0; i < change_coins.size(); i++) 
            {
                double coin = change_coins[i];
                if (coin >= 100) {
                    cout << coin / 100 << " dollars,";
                } else {
                    cout << coin << " cents,";
                }
            }
            SearchedItem->data->on_hand = SearchedItem->data->on_hand - 1;
        }
    }
    UpdateCoinFile(coins, "coins.dat");
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

void Option_4(LinkedList *LinkedList)
{
    string newID;
    string newName;
    string newdescription;
    double EnterPrice;
    int dollor;
    int cents;
    unsigned Newon_hands;
    bool LoopContinue = true;
    bool NewIDloopContinue = true;
    int NumberOfError = 0;
    while(LoopContinue == true)
    {
        while(NewIDloopContinue == true)
        {
            NumberOfError = 0;
            cout << "The ID of the new stock will be(you can type 'help' to see what should enter): ";
            cin >> newID;
            if(newID == "help")
            {
                cout << "In this situation, you should type a new item ID, and follow the format:" << endl;
                cout << "start with 'I' with 4 interger like I0009."<< endl;
                cout << "also the ID should be new." << endl;
            }
            else
            {
                cout <<endl;
                if(newID.length() != 5)
                {
                    NumberOfError++;
                    cout << "The ID is more or less than 5, it should be 5." << endl;
                }
                if(newID[0] != 'I')
                {
                    NumberOfError++;
                    cout << "The ID should start as 'I'" << endl;
                }
                for (int i = 1; i < 5; i++)
                {
                    if (!std::isdigit(newID[i]))
                    {
                        NumberOfError++;
                        cout << "In the number part, your " << i << " number is not interger, it should be interget." << endl;
                    }
                }
                if(LinkedList->checkItem(newID) == true)
                {
                    cout << "The ID is already there, try another." << endl;
                    NumberOfError++;
                }
                if(NumberOfError > 0)
                {
                    NewIDloopContinue = true;
                    cout << "Plase enter a valid ID or you can type a 'help' to help you." << endl;
                }
                else
                {
                    NewIDloopContinue = false;
                }
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        bool NewNamecontinue = true;
        while (NewNamecontinue == true)
        {
            cout << "Enter the item name(you can type 'help' to see what should enter): ";
            getline(cin,newName);
            if(newName == "help")
            {
                cout << "In here, you should type the name of the new item like 'putting', 'apple pie' etc and the number of character should less than 40." << endl;
            }
            else
            {
                if(newName.length() > 40)
                {
                    cout << "Your name's character is large than 40, it should be less, you can type a 'help' to help you." << endl;
                    NewNamecontinue = true;
                }
                else
                {
                    NewNamecontinue = false;
                }
            }   
        }
       
        bool Discriptioncontinue = true;
        while (Discriptioncontinue == true)
        { 
            cout << "Enter the item description(you can type 'help' to see what should enter): ";
            getline(cin,newdescription);
            if(newdescription == "help")
            {
                cout << "In this situation, you should type a long description to descrip your item, like 'this is a big and delicious pie.'etc." << endl;
            }
            else
            {
                if(newdescription.length() > 255)
                {
                    Discriptioncontinue = true;
                    cout << "Your description is too " << endl;
                }
                else
                {
                    Discriptioncontinue = false;
                }
            }
        }
        
        cout << "Enter the price for the item: ";
        
        if(!(cin >> EnterPrice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            NumberOfError++;
            dollor = 0;
            cents = 0;
        }
        else
        {
            dollor = static_cast<int>(EnterPrice);
            double Centspart = EnterPrice - dollor;
            cents = static_cast<int>(Centspart * 100);
        }
        cout << "Enter the item you have: ";
        if(!(cin >> Newon_hands))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            NumberOfError++;
        }
        if (NumberOfError != 0)
        {
            cout << "The item cannot be added to the list" << endl;
            cout << "Make sure the id is form as start of 'I' with 4 inter number; name is less than 40; description is less than 255; price enter as double; on_hand enter as inter." << endl;
        }
        else
        {
            LoopContinue = false;
        }
    }
    Stock item;
    item.id = newID;
    item.name = newName;
    item.description = newdescription;
    item.price.dollars = static_cast<unsigned int>(dollor);
    item.price.cents = static_cast<unsigned int>(cents);
    item.on_hand = static_cast<unsigned int>(Newon_hands);
    LinkedList->addBack(item);
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
    for (size_t i = 0; i < coins.size(); i++)
    {
        coins[i].Display();
    }
}

void Option_7(LinkedList* stockList){
    ifstream input("new_stock.dat");
    ofstream output("stock.dat");
    string line;
    while(getline(input,line)){
        output<<line<<endl;
    }
    stockList->deleteLinkedList();
    vector<Stock> items = loadStocks("stock.dat");
    for (size_t i = 0; i < items.size(); i++)
    {
        stockList->addBack(items[i]);
    }
    std::cout<<"All stocks has been reset to the default value of "<<DEFAULT_STOCK_LEVEL<<std::endl;

}


void Option_8(vector<Coin> coins)
{
    ifstream input("new_coins.dat");
    if (!input.is_open()) {
        cout << "Failed to open new_coin.dat" << endl;
        return;
    }

    ofstream output("coins.dat");
    if (!output.is_open()) {
        cout << "Failed to open coin.dat" << endl;
        input.close();
        return;
    }

    string line;
    while (getline(input, line)) {
        output << line << endl;
    }

    input.close();
    output.close();

    cout << "Coin file reset." << endl;
}

int main(int argc, char **argv)
{
    //write stokes into items vector
    vector<Stock> items = loadStocks("stock.dat");
    LinkedList stockList;
    //add items to list
    for (size_t i = 0; i < items.size(); i++)
    {
        stockList.addBack(items[i]);
    }
    
    vector<Coin> coins = loadCoin("coins.dat");
    
    bool MenuContinue = true;
    string optionInstring;
    int option;
    while( MenuContinue != false )
    {   
        cout << endl;
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
        cout << "Select your option (1-9)(you can type 'help' to see what should enter): ";
        cin >> optionInstring;
        cout << endl;
        if (optionInstring == "help")
        {
            cout << "\tIn here, you should type a interger number 1-9 to use different funcions." << endl;
        }
        else
        {
            try
            {
                option = stoi(optionInstring);
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
                    string filename = "stock.dat";
                    Option_3(filename, stockList);
                    MenuContinue = false;
                }
                else if(option == 4)
                {
                    Option_4(&stockList);
                }
                else if(option == 5)
                {
                    Option_5(&stockList);
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
                    Option_7(&stockList);
                }
                else if(option == 8)
                {
                    Option_8(coins);
                }
                else if(option == 9)
                {
                    cout << "bye!" << endl;
                    MenuContinue = false;
                }
                else
                {
                    std::cout << "Please enter 1~9"<< std::endl;
                    std::cout << std::endl;
                    option = 0;
                }
            }
            catch (const invalid_argument &ia)
            {
                cerr << "Please inter a interger number 1~9 or use 'help' to see what you can do here." << endl;
            }
        }
        
    }
    
    
    return EXIT_SUCCESS;
}
