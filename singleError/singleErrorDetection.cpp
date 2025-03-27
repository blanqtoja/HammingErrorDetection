
//
// Created by olek1 on 26/03/2025.
//

#include "singleErrorDetection.h"
#include <iostream>


std::vector<bool> singleErrorDetection(std::vector<bool> message, const std::vector<std::vector<bool>>& hammingMatrix) {

    // odnajdywanie bledu
    std::vector<bool> error;
    getErrorVector(message, error, hammingMatrix);

    std::cout << "syndrom bledu"<<std::endl;
    std::cout << vectorToString(error) << std::endl;

    fixSingleError(message, error, hammingMatrix);
    std::cout << "poprawiona wiadomosc"<<std::endl;
    std::cout << vectorToString(message) << std::endl;

    return error;
}

/*
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
*/
void fixSingleError(std::vector<bool>& message, const std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix ) {

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


