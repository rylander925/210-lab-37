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

int gen_hash_index(string);
void read_file(string filename, map<int, list<string>>& hash_table);
void hash_table_add(string str, map<int, list<string>>& hash_table);
void hash_table_display(int display_amount, map<int, list<string>>& hash_table, int spacing = 10);

int main() {
    const string FILENAME = "data.txt";
    const int DISPLAY_AMOUNT = 100;
    map<int, list<string>> hash_table;

    read_file(FILENAME, hash_table);
    hash_table_display(DISPLAY_AMOUNT, hash_table);
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
