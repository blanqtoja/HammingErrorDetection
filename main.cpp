#include <bitset>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "./doubleError/doubleErrorDetection.h"
#include "./singleError/singleErrorDetection.h"

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
        option = '0'; // reset option
        do{
            std::cout << "1) single error";
            std::cout << "2) single/double error";
            std::cout << "Enter an option: ";

        } while(option != '1' && option != '2');

        std::string message;
        std::cout << "Enter a message: ";
        std::cin >> message;
        std::vector<bool> messange;
        for (auto i : message) {
            messange.push_back(i);
        }

        if(option == '1') {

            singleErrorDetection(messange);
        }
        else if(option == '2'){
            doubleErrorDetection(messange);
        }
    }
    else if (option == '2') {

        std::string message;
        std::cout << "Enter a file name: ";
        std::cin >> message;

        std::ifstream file(message, std::ios::binary);
        if (!file) {
            std::cerr << "Nie można otworzyć pliku!" << std::endl;
            return 1;
        }

        // Sprawdzenie rozmiaru pliku
        std::streamsize fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        std::cout << "Rozmiar pliku: " << fileSize << " bajtów" << std::endl;


//        // Wyświetlenie wartości bajtów jako liczby
//        for (char c : buffer) {
//            std::cout << std::hex << static_cast<int>(static_cast<unsigned char>(c)) << " ";
//        }

        file.close();


    }


    return 0;
}
