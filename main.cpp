#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>

#include "./doubleError/doubleErrorDetection.h"
#include "./singleError/singleErrorDetection.h"

std::vector<bool> charToBoolV8 (char c) {
    std::vector<bool> v;
    int a = c;
    int i=0;
    while (i < 8) {
        v.push_back(a%2);
        a /= 2;
        i++;
    }

    std::reverse(v.begin(), v.end());
    return v;
}


char vectorToChar(const std::vector<bool>& bits) {


    std::bitset<8> bitset;
    for (size_t i = 0; i < 8; i++) {
        bitset[7 - i] = bits[i];  // Przepisujemy bity w odwrotnej kolejności
    }

    return static_cast<char>(bitset.to_ulong());
}


int main() {

    // std::vector<bool> messange = { 1,0,1,0,1,0,1,0};
    // doubleErrorDetection(messange);

    char option;
    std::cout << "Hamming errors detection\n\n";
    std::cout << "1) write a message\n";
    std::cout << "2) file\n";
    std::cout << "Enter an option: \n";
    std::cin >> option;

    if (option == '1') {
        option = '0'; // reset option
        do{
            std::cout << "1) single error\n";
            std::cout << "2) single/double error\n";
            std::cout << "Enter an option: \n";
            std::cin >> option;
        } while(option != '1' && option != '2');

        std::string message;
        // zapewniamy, ze wiadomosc ma 8 bitow
        do {
            std::cout << "Enter message (8 bits): \n";
            std::cin >> message;
        } while (message.size() != 8);

        std::vector<bool> messageV;
        for (auto i : message) {
            // char to bool
            // przyjmujemy, ze jesli jest cos innego niz 1, to jest to 0
            i == '1' ? messageV.push_back(1) : messageV.push_back(0);
        }

        if(option == '1') {
            //korekcja jednego bledu
            //    2^k >= m+k+1
            std::vector<std::vector<bool>> hammingMatrix = {
                {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0},
                {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0},
                {1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0},
                {1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1}
            };

            // kodowanie wiadomosci
            encodeMessage(messageV, hammingMatrix);
            std::cout << "Encoded message: \n"
            << vectorToString(messageV) << std::endl;

            // zapewniamy, ze wiadomosc ma 12 bitow
            do {
                std::cout << "Make an mistake: \n";
                std::cin >> message;
            } while (message.size() != 12);

            messageV.clear();
            for (auto i : message) {
                // przyjmujemy, ze jesli jest cos innego niz 1, to jest to 0
                i == '1' ? messageV.push_back(1) : messageV.push_back(0);
            }

            std::vector<bool> error;
            getErrorVector(messageV, error, hammingMatrix);

            std::cout << "Error syndrome: " << vectorToString(error) << std::endl;

            fixSingleError(messageV, error, hammingMatrix );
            std::cout << "Corrected message: " << vectorToString(messageV) << std::endl;

        }
        else if(option == '2'){

            // https://www.researchgate.net/publication/228819322_A_16_8_error_correcting_code_t_2_for_critical_memory_applications
            std::vector<std::vector<bool>> hammingMatrix ={
                { 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                { 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                { 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                { 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
                { 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
                { 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                { 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
                { 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
            };

            // kodowanie wiadomosci
            encodeMessage(messageV, hammingMatrix);
            std::cout << "Encoded message: \n"
            << vectorToString(messageV) << std::endl;

            // zapewniamy, ze wiadomosc ma 16 bitow
            do {
                std::cout << "Make an mistake: \n";
                std::cin >> message;
            } while (message.size() != 16);

            messageV.clear();
            for (auto i : message) {
                // przyjmujemy, ze jesli jest cos innego niz 1, to jest to 0
                i == '1' ? messageV.push_back(1) : messageV.push_back(0);
            }

            std::vector<bool> error;
            getErrorVector(messageV, error, hammingMatrix);

            std::cout << "Error syndrome: " << vectorToString(error) << std::endl;

            fixDoubleError(messageV, error, hammingMatrix );
            std::cout << "Corrected message: " << vectorToString(messageV) << std::endl;
        }
    }
    else if (option == '2') {
        std::vector<std::vector<bool>> hammingMatrix ={
            { 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            { 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            { 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
            { 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
            { 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            { 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
            { 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
        };

        std::string fileName;
        std::cout << "Enter a file name: \n";
        std::cin >> fileName;
        std::string path = std::filesystem::current_path().parent_path();


        std::ifstream file(path + '/' + fileName);
        if (!file) {
            return 1;
        }

        // otwieramy plik do zapisu bitow
        std::ofstream saveFile(path + "/save_" + fileName);

        if (!saveFile) {
            return 1;
        }

        char c;
        while (file.get(c)) {
            std::vector<bool> messageV = charToBoolV8(c);

            std::cout << vectorToString(messageV) << std::endl;

            // Kodowanie wiadomości
            encodeMessage(messageV, hammingMatrix);
            std::cout << vectorToString(messageV) << std::endl;

            saveFile << vectorToString(messageV);

            // Dopisz enter, jeśli to nie koniec pliku
            if (file.peek() != EOF) {  // Sprawdzamy następny znak
                saveFile << std::endl;
            }
        }
        file.close();
        saveFile.close();

        std::cout<<"You can do mistakes in file :)" << std::endl;
        std::string input;
        std::cin>>input;

        //odkodowanie

        std::ifstream binCharFile(path + "/save_" + fileName);
        if (!binCharFile) {
            return 1;
        }

        std::ofstream decrFile(path + "/decrypted_" + fileName);

        if (!decrFile) {
            return 1;
        }

        while (!binCharFile.eof()){
            std::vector<bool> messageV;
            int i;
            for ( i=0 ; i<16 && !binCharFile.eof(); i++){
                binCharFile.get(c);


                messageV.push_back(c-48);
            }
            if (!binCharFile.eof()) {
                binCharFile.get(c);
            }
            else {
                reverse(messageV.begin(), messageV.end());
                for ( ; i<16; i++) {
                    messageV.push_back(0);
                }
                reverse(messageV.begin(), messageV.end());
            }




            // sprawdzanie bledow
            std::vector<bool> error;
            getErrorVector(messageV, error, hammingMatrix);

            std::cout << "Error syndrome: " << vectorToString(error) << std::endl;

            fixDoubleError(messageV, error, hammingMatrix );
            decrFile << vectorToChar(messageV);

            // std::cout << vectorToString(messageV) << std::endl;
            // std::cout << vectorToChar(messageV) << std::endl;

            messageV.clear();
        }


    }


    return 0;
}
