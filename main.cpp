#include <bitset>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "./doubleError/doubleErrorDetection.h"

int main() {

    std::vector<bool> messange = { 1,0,1,0,1,0,1,0};
    doubleErrorDetection(messange);

    char option;
    std::cout << "Hamming errors detection";
    std::cout << "1) write a message";
    std::cout << "2) file";
    std::cout << "Enter an option: ";
    std::cin >> option;

    if (option == '1') {

    }
    else if (option == '2') {

    }


    return 0;
}
