//
// Created by olek1 on 26/03/2025.
//

#include "doubleErrorDetection.h"

void doubleErrorDetection(std::vector<bool> message) {

    // https://www.researchgate.net/publication/228819322_A_16_8_error_correcting_code_t_2_for_critical_memory_applications
    std::vector<std::vector<bool>> H ={
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0}
    };

    std::cout << "wiadomosc oryginal"<<std::endl;
    std::cout << vectorToString(message) << std::endl;


    //zakodowanie
    encodeMessage(message, H);

    std::cout << "wiadomosc encoded"<<std::endl;
    std::cout << vectorToString(message) << std::endl;

    // wprowadzenie ledu
    // zamień drugie miejsce w wektorze na 1
    message[2] = 0;
    message[0] = 0;
    std::cout << "wiadomosc z bledem"<<std::endl;
    std::cout << vectorToString(message) << std::endl;


    // odnajdywanie bledu
    std::vector<bool> error;
    getErrorVector(message, error, H);

    std::cout << "syndrom bledu"<<std::endl;
    std::cout << vectorToString(error) << std::endl;

    fixError(message, error, H);
    std::cout << "poprawiona wiadomosc"<<std::endl;
    std::cout << vectorToString(message) << std::endl;
}
// todo: napisac metode ktora sprawdza suma ktrorych dwoch kolumn jest rowna error
/*
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
}*/
