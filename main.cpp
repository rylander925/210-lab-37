/*
COMSC-210 | Lab 37 | Rylan Der
IDE Used: Visual Studio Code
*/

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <fstream>
using namespace std;

int gen_hash_index(string);
void read_file(string filename, map<int, list<string>>& hash_table);
void hash_table_add(string str, map<int, list<string>>& hash_table);

int main() {
    const string FILENAME = "data.txt";
    map<int, list<string>> hash_table;
    cout << read_file(FILENAME) << endl;

    return 0;
}

/* 
These targets are present in the dataset and can be used for testing:
536B9DFC93AF
1DA9D64D02A0
666D109AA22E
E1D2665B21EA
*/

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
