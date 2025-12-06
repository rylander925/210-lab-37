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
void hash_table_search(string str, map<int, list<string>>& hash_table);
void hash_table_display(int display_amount, map<int, list<string>>& hash_table, int spacing = 10);

int main() {
    const string FILENAME = "data.txt";
    const int DISPLAY_AMOUNT = 100;
    enum Options{DISPLAY = 1, SEARCH = 2, ADD = 3, REMOVE = 4, MODIFY = 5, EXIT = 6};

    map<int, list<string>> hash_table;
    int option;
    read_file(FILENAME, hash_table);

    do {
        //Display menu
        cout << "Menu options: " << endl;
        cout << " " << DISPLAY << ". Display first 100 entries" << endl;
        cout << " " << SEARCH << ". Search for a key" << endl;
        cout << " " << ADD << ". Add a key" << endl;
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
                string query;
                cout << "Enter a string to search for > ";
                getline(cin, query);
                hash_table_search(query, hash_table);
                break;
        }
    } while (option != EXIT);
    cout << "Exiting" << endl;
}
/**
 * If found, outputs the hash index and list position of the given string in the hash table.
 * @param str String to find
 * @param hash_table Hash table to search
 */
void hash_table_search(string str, map<int, list<string>>& hash_table) {
    int index = gen_hash_index(str);
    if (hash_table.find(index) != hash_table.end()) {
        //If hash index is found, finds the position of the string in the list
        int list_pos = 0;
        auto it = hash_table.at(index).begin();
        while (it != hash_table.at(index).end() && *it != str) { //iterates until end of list or until it finds the string to track list position
            it++;
            list_pos++;
        }

        //if found, outputs index and list position, or error otherwise
        if (it != hash_table.at(index).end()) {
            cout << "Key \"" << str << "\" found at hash index " << index << ", list index " << list_pos << endl;
        } else {
            cout << "Key \"" << str << "\" not found." << endl;
        }
    } else {
        cout << "Key \"" << str << "\" not found." << endl;
    }
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
