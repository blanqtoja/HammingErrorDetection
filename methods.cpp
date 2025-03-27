//
// Created by olek1 on 26/03/2025.
//

#include "methods.h"

#include <iostream>

bool getParity(const std::vector<bool>& message, const std::vector<std::vector<bool>>& hammingMatrix, uint8_t row) {
     int sum = 0;
     for (int j=0; j < message.size(); j++) {
         sum+= message.at(j) * hammingMatrix[row][j];
     }

     return sum%2 == 1;

    /*bool sum = 0;
    for (int j=0; j < message.size(); j++) {
        sum ^=  message.at(j) & hammingMatrix[row][j];
    }

    return sum;*/
}

std::string vectorToString(const std::vector<bool>& message) {
    std::string str;
    for (auto b : message) {
        str += std::to_string(b);
    }
    return str;
}

//zakodowanie wiadomosci
void encodeMessage(std::vector<bool>& message, const std::vector<std::vector<bool>>& hammingMatrix) {

    for (int i=0; i < hammingMatrix.size(); i++) {
        message.push_back(getParity(message, hammingMatrix, i));
    }
}

void getErrorVector(const std::vector<bool>& message, std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix ) {

    for (int i=0; i < hammingMatrix.size(); i++) {
        error.push_back(getParity(message, hammingMatrix, i));
    }
}


// single method
/*void fixError(std::vector<bool>& message, const std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix ) {

    //zabezpieczenie, ze mnozenie jest mozliwe
    if (message.size() != hammingMatrix[0].size()) {
        std::cout << "Error message size doesn't match hamming matrix size" << std::endl;
        return;
    }

    for (int i = 0 ; i<message.size(); i++) {
        bool errorFound = true;
        for (int j=0; j<error.size(); j++) {
            //jesli kolumna rozwni sie czymkolwiek, to przerwij
            if (error.at(j) != hammingMatrix[j][i] ) {
                errorFound = false;
            }
        }

        if (errorFound) {
            //odwracamy bledny bit
            // std::cout << "blad na: " << i<< "bicie"<<std::endl;
            message.at(i) = !message.at(i);
        }

    }
}*/


void fixError(std::vector<bool>& message, const std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix) {
    // Sprawdzamy, czy rozmiar wiadomości pasuje do macierzy Hamming'a
    if (hammingMatrix.empty() || message.size() != hammingMatrix[0].size()) {
        std::cout << "Error: message size doesn't match hamming matrix size" << std::endl;
        return;
    }

    int numColumns = hammingMatrix[0].size();  // Liczba kolumn macierzy


    // pierwszy przypadek -> szukamy, czy mamy do czynienia z pojedynczym bledem
    //zabezpieczenie, ze mnozenie jest mozliwe
    if (message.size() != hammingMatrix[0].size()) {
        std::cout << "Error message size doesn't match hamming matrix size" << std::endl;
        return;
    }

    for (int i = 0 ; i<message.size(); i++) {
        bool errorFound = true;
        for (int j=0; j<error.size(); j++) {
            //jesli kolumna rozwni sie czymkolwiek, to przerwij
            if (error.at(j) != hammingMatrix[j][i] ) {
                errorFound = false;
            }
        }

        if (errorFound) {
            //odwracamy bledny bit
            // std::cout << "blad na: " << i<< "bicie"<<std::endl;
            message.at(i) = !message.at(i);
            //znaleziony blad, mozemy przerwac
            return;
        }

    }


    //przechodzimy do szukania dwoch bledow
    // Przeszukujemy wszystkie pary kolumn
    for (int firstCol = 0; firstCol < numColumns; firstCol++) {
        for (int secondCol = firstCol + 1; secondCol < numColumns; secondCol++) {  // secondCol > firstCol, żeby unikać duplikatów

            std::vector<bool> sumV(error.size());

            //test
            if ( firstCol == 2 && secondCol == 9) {}

            // XOR dwóch kolumn
            for (size_t i = 0; i < error.size(); i++) {
                sumV[i] = hammingMatrix[i][firstCol] ^ hammingMatrix[i][secondCol];
            }

            // Sprawdzamy, czy suma dwóch kolumn odpowiada wektorowi błędu
            if (sumV == error) {
                // std::cout << "Znaleziono dwie kolumny błędu: " << firstCol << " i " << secondCol << std::endl;
                // std::cout << "Kolumna " << firstCol << std::endl;
                // std::cout << "Kolumna " << secondCol <<  std::endl;

                // naprawiamy blad
                message[firstCol] = !message[firstCol] ;
                message[secondCol] = !message[secondCol] ;

                return;  // Możemy zakończyć, bo znaleźliśmy błąd
            }


        }
    }

    std::cout << "Nie znaleziono pasujących kolumn." << std::endl;
}