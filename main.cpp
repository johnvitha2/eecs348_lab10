#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <cmath>
using namespace std;

/*
* Take a char as a parameter and return true if it is a digit 0-9
*/
bool is_digit(char ch){
    if(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9'){ // check digits 1-9
        return true; // char is a digit
    }
    return false; // char is not a digit
}

/*
* Take a char as a parameter and return the digit it represents
*/
double get_digit(char dig){ 
    if(dig == '0'){ 
        return 0;
    } else if(dig == '1'){
        return 1;
    } else if(dig == '2'){
        return 2;
    } else if(dig == '3'){
        return 3;
    } else if(dig == '4'){
        return 4;
    } else if(dig == '5'){
        return 5;
    } else if(dig == '6'){
        return 6;
    } else if(dig == '7'){
        return 7;
    } else if(dig == '8'){
        return 8;
    } else if(dig == '9'){
        return 9;
    }
    return -1;
}

/*
* Load string-formatted numbers from a user-specified file, where each line in the file contains two potential doubles
*/
array<string, 60> read_file(ifstream &file){ 
    array<string, 60> strs; // Initialize an array of strings strs with size 60
    for (int i = 0; i < 60; i += 2){ // Loop through each line in the file
        file >> strs[i] >> strs[i+1]; // Save both doubles in the line to strs
    }
    return strs; // Return the array of strings representing doubles
}

/*
* Return true if str is a valid double number, else return false
*/
bool is_valid_double(string str){
    for (size_t i = 0; i < str.length(); i++){ // Loop through each char in the string
        if(!is_digit(str[i])){ // If not a digit
            if(str[i] == '.'){ // If it is decimal point
                if(i+1 == str.length()){ // String cannot end with a decimal point
                    return false;
                } else if(!is_digit(str[i+1])){ // Char after decimal point must be a digit
                    return false;
                }
            } else if(str[i] == '+' || str[i] == '-'){ // If it is a +/- sign
                if(i+1 == str.length()){ // String cannot end with a sign
                    return false;
                } else if(!is_digit(str[i+1])){ // Char after sign must be a digit
                    return false;
                }
            } else {
                return false; // Return false if char is not a digit, '.', or '(+/-)'
            }
        }
    }
    return true; // Double is valid
}

/*
* Take a string representing a double as a parameter and return a copy of type double
*/
double double_copy(string double_string){ 
    double new_double = 0; // New double to return
    double sign = 1; // Sign of double, assume positive
    int place = 0; // Counter for place before the decimal
    int decimal_place = 0; // Counter for decimal place
    double place_multiplier = 1.0; 
    bool has_decimal = false;

    if(double_string[0] == '-'){ // If double is negative
        sign = -1; // Change sign to negative
        double_string.erase(0, 1); // Erase the sign to make the string easier to read
    } else if(double_string[0] == '+'){ // If double is positive
        double_string.erase(0, 1); // Erase the sign to make the string easier to read
    }

    for(size_t i = 0; i < double_string.length(); i ++){ // Loop through each 
        if(double_string[i] == '.'){ // If decimal is reached
            has_decimal = true; 
        }
        if(!has_decimal){ // If decimal not reached yet/there is no decimal
            place++; // Increment place up 1
        }
    }
    if(has_decimal){ // If double has a decimal
        decimal_place = double_string.length() - (place+1); // Calculate the decimal place
    }
    

    for(int i = 1; i < place; i++){ 
        place_multiplier *= 10.0; // Calculate the place of the first digit in the double
    }
    for(size_t i = 0; i < double_string.length(); i++){ // Loop through each character in the string
        if(double_string[i] != '.'){ // If not at the decimal point
            if(place != 0){ // If there are still numbers before the decimal point
                new_double += place_multiplier*get_digit(double_string[i]); // Add the value of the digit at i to the new double
                place--; // Increment place down 1
                place_multiplier /= 10.0; // Update the place multiplier
            } else if(decimal_place != 0){ // If there is a decimal place
                new_double += get_digit(double_string[i])/place_multiplier; // Add the value of the digit at i to the new double
                decimal_place--; // Increment decimal place down 1
                place_multiplier *= 10.0; // Update the place multiplier
            } 
        }  else {
            place_multiplier = 10.0; // Reset the place multiplier for decimal places
        }
    }
    return new_double*sign; // Return the new double
} 

/*
* Return the sum of two doubles in string format using make_double(string double_string)
*/
double sum(string addend1, string addend2){
    return double_copy(addend1) + double_copy(addend2); // Return the sum
}

int main(){
    string filename; 
    ifstream file; 
    array<string, 60> strs; // Intialize an array to hold double strings

    while(1){ // Repeat until valid file 
        cout << "Enter a file: "; 
        cin >> filename;
        file.open(filename); // Try to open the file
        if(file) break; // Exit loop if valid file
        cout << "Invalid file. Please try again." << endl; // If the file is invalid, ask the user to try again
    }
    strs = read_file(file);
    for (int i = 0; i < 60; i += 2){
        if(is_valid_double(strs[i]) && is_valid_double(strs[i+1])){ // If both strings represent valid doubles
            cout << strs[i] << " and " << strs[i+1] << " are both valid double numbers. Sum: " << sum(strs[i], strs[i+1]) << endl;
        } else if(is_valid_double(strs[i])){
            cout << "The pair " << strs[i] << " and " << strs[i+1] << " is invalid: " << strs[i+1] << " is not a valid double number." << endl;
        } else if(is_valid_double(strs[i+1])){
            cout << "The pair " << strs[i] << " and " << strs[i+1] << " is invalid: " << strs[i] << " is not a valid double number." << endl;
        } else {
            cout << strs[i] << " and " << strs[i+1] << " are both invalid double numbers." << endl;
        }
    }
}


