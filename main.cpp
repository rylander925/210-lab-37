/*
COMSC-210 | Lab 38 | Rylan Der
IDE Used: Visual Studio Code
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <fstream>
using namespace std;

const int STREAM_IGNORE_CHARS = 100;

int gen_hash_index(string);
void read_file(string filename, map<int, list<string>>& hash_table);
void hash_table_add(string str, map<int, list<string>>& hash_table);
list<string>::iterator hash_table_search(string str, map<int, list<string>>& hash_table);
bool hash_table_remove(string str, map<int, list<string>>& hash_table);
void hash_table_display(int display_amount, map<int, list<string>>& hash_table, int spacing = 10);

int main() {
    const string FILENAME = "data.txt";
    const int DISPLAY_AMOUNT = 100;
    enum Options{DISPLAY = 1, SEARCH = 2, ADD = 3, REMOVE = 4, MODIFY = 5, EXIT = 6};

    map<int, list<string>> hash_table;
    int option;
    string user_string;
    read_file(FILENAME, hash_table);

    do {
        //Display menu
        cout << "Menu options: " << endl;
        cout << " " << DISPLAY << ". Display first 100 entries" << endl;
        cout << " " << SEARCH << ". Search for a key" << endl;
        cout << " " << ADD << ". Add a key" << endl;
        cout << " " << REMOVE << ". Remove a key" << endl;
        cout << " " << MODIFY << ". Modify a key" << endl;
        cout << " " << EXIT << ". Exit" << endl;
        do {
            //retrieve input for menu option
            cout << "Enter menu choice: > ";
            cin >> option;

            //validate option input
            if (cin.fail()) {
                cout << "Option must be an integer" << endl;
                option = DISPLAY - 1;
            } else if (option < DISPLAY || option > EXIT) {
                cout << "Option must be in range " << DISPLAY << " - " << EXIT << " inclusive" << endl;
            }
            cin.clear();
            cin.ignore(STREAM_IGNORE_CHARS, '\n');
        } while (option < DISPLAY || option > EXIT);

        //execute menu function based on option
        switch (option) {
            case DISPLAY:
                cout << "Displaying first 100 entries" << endl;
                hash_table_display(DISPLAY_AMOUNT, hash_table);
                break;
            case SEARCH:
                cout << "Enter a string to search for > ";
                getline(cin, user_string);
                hash_table_search(user_string, hash_table);
                break;
            case ADD:
                cout << "Enter a string to add > ";
                getline(cin, user_string);
                hash_table_add(user_string, hash_table);
                cout << "Added key \"" << user_string << "\" at hash index " << gen_hash_index(user_string) << endl; 
                break;
            case REMOVE:
                cout << "Enter a string to remove > ";
                getline(cin, user_string);
                if (hash_table_remove(user_string, hash_table)) cout << "Removed key \"" << user_string << "\"" << endl;
                break;
            case MODIFY: //modifies by removing then adding string
                cout << "Enter a string to modify > ";
                getline(cin, user_string);
                if (hash_table_remove(user_string, hash_table)) {
                    cout << "Enter a replacement string > ";
                    getline(cin, user_string);
                    hash_table_add(user_string, hash_table);
                    cout << "Successfully modified to \"" << user_string << "\"" << endl;
                }
                break;
        }
        cout << endl;
    } while (option != EXIT);
    cout << "Exiting" << endl;
}

/**
 * Removes the first instance of a string from the hash table if found
 * @param str String to remove
 * @param hash_table Hash table to search and remove from
 * @return Returns true if element was found and deleted, false otherwise
 */
bool hash_table_remove(string str, map<int, list<string>>& hash_table) {
    //searches for string
    auto it = hash_table_search(str, hash_table);
    if (it != hash_table.begin()->second.end()) {//error value returned if not found

        //removes that instance of the string, will not remove all duplicates if present
        hash_table.at(gen_hash_index(str)).erase(it);
        return true;
    }
    return false;
}

/**
 * If found, outputs the hash index and list position of the given string in the hash table, and returns an iterator to that element.
 * @param str String to find
 * @param hash_table Hash table to search
 * @return Iterator to element if found, or iterator to the end of the list of the hash tables beginning iterator
 * @note If not found, returns iterator to a list element (of the first list in the hash_table) 
 */
list<string>::iterator hash_table_search(string str, map<int, list<string>>& hash_table) {
    int index = gen_hash_index(str);
    if (hash_table.find(index) != hash_table.end()) {
        //If hash index is found, finds the position of the string in the list
        int list_pos = 0;
        auto it = hash_table.at(index).begin();
        while (it != hash_table.at(index).end() && *it != str) { //iterates until end of list or until it finds the string to track list position
            it++;
            list_pos++;
        }

        //outputs index and list position if found
        if (it != hash_table.at(index).end()) {
            cout << "Key \"" << str << "\" found at hash index " << index << ", list index " << list_pos << endl;
            return it; //returns iterator to specified element if found
        }
    }
    cout << "Key \"" << str << "\" not found." << endl;
    return hash_table.begin()->second.end(); //returns iterator to end of the first hash_index's list as an error value
}

/**
 * Displays the first of a specified number of elements in the given hash table
 * @param display_amount Number of elements to display
 * @param hash_table Hash table whose elements will be displayed 
 * @param spacing Spacing between table columns
 */
void hash_table_display(int display_amount, map<int, list<string>>& hash_table, int spacing) {
    cout << setw(spacing) << left << "Number" << setw(spacing) << left << "Index" << setw(spacing) << left << "Value" << endl; //display table header

    int num = 0;
    //iterate through hash_table to DISPLAY_AMOUNT or the size of the hash table
    for (map<int, list<string>>::iterator it = hash_table.begin(); num < display_amount && it != hash_table.end(); it++) {
        //iterate through list associated with each index, incrementing i for each value outputted to display correct number of values
        for (string str : it->second) {
            cout << setw(spacing) << left << " " + to_string(num + 1) + "." << setw(spacing) << left << it->first << setw(spacing) << left << str << endl;
            num++;
        }
    }
}

/**
 * Adds a string to the given hash table
 * @param str String to add
 * @param hash_table Hash table to add to
 */
void hash_table_add(string str, map<int, list<string>>& hash_table) {
    hash_table[gen_hash_index(str)].push_front(str); //adds string to the front of the list of the associated hash index
}

/**
 * Reads file contents into given hash table
 * @param filename File to read
 * @param hash_table Hash table to populate
 */
void read_file(string filename, map<int, list<string>>& hash_table) {
    //validate file opens properly
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open()) {
        cout << "ERROR: Could not open file \"" << filename << "\"" << endl;
        throw ios_base::failure("File open error");
    }

    //iterate through file and process contents
    string str;
    while(getline(infile, str)) {
        hash_table_add(str, hash_table);
    }
}

/**
 * Generates a hash index for the given string
 * Currently calculated as the sum of ascii values
 * @param str Calculates hash value of this string
 * @return Hash index of the string
 */
int gen_hash_index(string str) {
    int sum = 0;
    for (char c : str) { //iterate through each character in str
        sum += (int) c;  //sum ascii value of each char
    }
    return sum;
}
