#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib> // for atoi

using namespace std;

struct Item {
    int item_id;
    string item_name;
    int item_quantity;
    string item_registration_date;
};

// Function to add item to CSV file
void addItem(const string& filename, int item_id, const string& item_name, int item_quantity, const string& item_registration_date) {
    ofstream file(filename.c_str(), ios_base::app);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    file << item_id << "," << item_name << "," << item_quantity << "," << item_registration_date << endl;
    file.close();
}

// Function to list items in alphabetical order
bool compareItems(const Item& a, const Item& b) {
    return a.item_name < b.item_name;
}

void listItems(const string& filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    vector<Item> items;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Item item;
        string token;
        getline(ss, token, ',');
        item.item_id = atoi(token.c_str()); // Convert string to integer
        getline(ss, item.item_name, ',');
        getline(ss, token, ',');
        item.item_quantity = atoi(token.c_str()); // Convert string to integer
        getline(ss, item.item_registration_date, ',');
        items.push_back(item);
    }
    file.close();

    sort(items.begin(), items.end(), compareItems);

    // Display items
    cout << "Listing items:" << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        cout << "Item ID: " << items[i].item_id << endl;
        cout << "Item Name: " << items[i].item_name << endl;
        cout << "Quantity: " << items[i].item_quantity << endl;
        cout << "Reg Date: " << items[i].item_registration_date << endl << endl;
    }
}

int main() {
    string filename = "inventory.csv";
    string command;

    while (true) {
        cout << "Enter command: ";
        cin >> command;

        transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "itemadd") {
            int item_id, item_quantity;
            string item_name, item_registration_date;
            cin >> item_id >> item_name >> item_quantity >> item_registration_date;
            addItem(filename, item_id, item_name, item_quantity, item_registration_date);
        } else if (command == "itemslist") {
            listItems(filename);
        } else if (command == "help") {
            cout << "Command syntaxes:\n"
                 << "itemadd <item_id> <item_name> <quantity> <registration_date>\n"
                 << "itemslist\n"
                 << "exit\n";
        } else if (command == "exit") {
            break;
        } else {
            cout << "Error: Command not recognized. Type 'help' for assistance." << endl;
        }
    }

    return 0;
}

