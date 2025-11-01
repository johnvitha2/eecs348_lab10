#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <cmath>
using namespace std;

bool is_digit(char ch){
    if(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9'){
        return true;
    }
    return false;
}

array<string, 60> read_file(ifstream &file){
    array<string, 60> strs;
    for (int i = 0; i < 60; i += 2){
        file >> strs[i] >> strs[i+1];
    }
    return strs;
}

bool is_valid_double(string str){
    for (size_t i = 0; i < str.length(); i++){
        if(!is_digit(str[i])){
            if(str[i] == '.'){
                if(i+1 >= str.length()){
                    return false;
                } else if(!is_digit(str[i+1])){
                    return false;
                }
            } else if(str[i] == '+' || str[i] == '-'){
                if(i+1 >= str.length()){
                    return false;
                } else if(!is_digit(str[i+1])){
                    return false;
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}

double sum(string addend1, string addend2){
    return make_double(addend1) + make_double(addend2);
}

double make_double(string double_string){
    double new_double = 0;
    double sign = 1;
    int exp_sign = 1;
    int place = 0;
    int decimal_place;

    if(double_string[0] == '-'){
        sign = -1;
        double_string.erase(0, 1);
    } else if(double_string[0] == '+'){
        double_string.erase(0, 1);
    }

    while(place != double_string.length() && double_string[place] != '.'){
        place++;
    }

    decimal_place = double_string.length() - (place+1);

    for(size_t i = 0; i < double_string.length(); i++){
        if(double_string[i] != '.'){
            if(place != 0){
                new_double += pow(10, (place-1)*exp_sign)*get_digit(double_string[i]);
                place--;
            } else if(decimal_place != 0){
                new_double += pow(10, (decimal_place-1)*exp_sign)*get_digit(double_string[i]);
                decimal_place--;
            }
        } else {
            exp_sign = -1;
        }
    }
    return new_double*sign;
} 

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
}

int main(){
    string filename;
    ifstream file;
    array<string, 60> strs;

    while(1){
        cout << "Enter a file: ";
        cin >> filename;
        file.open(filename);
        if(file) break;
        cout << "Invalid file. Please try again." << endl;
    }
    strs = read_file(file);
    for (int i = 0; i < 60; i += 2){
        if(is_valid_double(strs[i]) && is_valid_double(strs[i+1])){
            cout << strs[i] << " and " << strs[i+1] << " are both valid doubles." << endl;
            cout << "Sum: " << sum(strs[i], strs[i+1]) << endl;
        } else {
            cout << "Line " << i << " does not represent a valid double." << endl;
        }
    }
}


