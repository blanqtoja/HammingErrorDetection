/*
//
// Created by olek1 on 26/03/2025.
//

#include "singleErrorDetection.h"
#include <iostream>

void singleErrorDetection(std::vector<bool> message) {
    //korekcja jednego bledu
    //    2^k >= m+k+1

    // dwuwymiarowa tablica bitow (k x m+k) -> (4x12)
    std::vector<std::vector<bool>> H_c4 = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1}
    };

    std::cout << "wiadomosc oryginal"<<std::endl;
    std::cout << vectorToString(message) << std::endl;


    //zakodowanie
    encodeMessage(message, H_c4);

    std::cout << "wiadomosc encoded"<<std::endl;
    std::cout << vectorToString(message) << std::endl;

    // wprowadzenie ledu
    // zamień drugie miejsce w wektorze na 1
    message[2] = 0;
    std::cout << "wiadomosc z bledem"<<std::endl;
    std::cout << vectorToString(message) << std::endl;


    // odnajdywanie bledu
    std::vector<bool> error;
    getErrorVector(message, error, H_c4);

    std::cout << "syndrom bledu"<<std::endl;
    std::cout << vectorToString(error) << std::endl;

    fixError(message, error, H_c4);
    std::cout << "poprawiona wiadomosc"<<std::endl;
    std::cout << vectorToString(message) << std::endl;
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
#1#
*/
