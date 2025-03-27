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
void fixError(std::vector<bool>& message, const std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix ) {

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
}