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

int main() {
    
    cout << sum_ascii("Tomato") << endl;
    cout << sum_ascii("tomato") << endl;
    cout << sum_ascii("  ") << endl;
    cout << sum_ascii("`1234567890-=~!@#$%^&*()_+") << endl;
    cout << sum_ascii("\n\t") << endl;

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
