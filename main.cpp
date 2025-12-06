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

int sum_ascii(string);
int read_file(string filename);

int main() {
    const string FILENAME = "data.txt";
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
 * Reads and processes file contents
 * Currently sums ascii values of file
 * @param filename File to read
 * @return sum of ascii values of file contents (not including newlines)
 */
int read_file(string filename) {
    //validate file opens properly
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open()) {
        cout << "ERROR: Could not open file \"" << filename << "\"" << endl;
        throw ios_base::failure("File open error");
    }

    //iterate through file and process contents
    int sum = 0;
    string str;
    while(getline(infile, str)) {
        sum += sum_ascii(str);
    }
    return sum;
}

/**
 * Sums ascii values of the characters of the given string
 * @param str String whose ascii values will be summed
 * @return Sum of ascii values as an integer
 */
int sum_ascii(string str) {
    int sum = 0;
    for (char c : str) { //iterate through each character in str
        sum += (int) c;  //sum ascii value of each char
    }
    return sum;
}
