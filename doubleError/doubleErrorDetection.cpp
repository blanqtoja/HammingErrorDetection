//
// Created by olek1 on 26/03/2025.
//

#include "doubleErrorDetection.h"

void doubleErrorDetection(std::vector<bool> message) {

    // https://www.researchgate.net/publication/228819322_A_16_8_error_correcting_code_t_2_for_critical_memory_applications
    std::vector<std::vector<bool>> H ={
        { 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        { 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        { 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        { 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        { 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        { 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        { 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        { 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
    };

    // 0 0   0
    // 1 1   0
    // 0 0   0
    // 1 0   1
    // 0 0   0
    // 0 0   0
    // 1 0   1
    // 1 0   1

    std::cout << "wiadomosc oryginal"<<std::endl;
    std::cout << vectorToString(message) << std::endl;


    //zakodowanie
    encodeMessage(message, H);

    std::cout << "wiadomosc encoded"<<std::endl;
    std::cout << vectorToString(message) << std::endl;

    // wprowadzenie ledu
    // zamień drugie miejsce w wektorze na 1
    message[2] = 0;
    // message[9] = 0;
    std::cout << "wiadomosc z bledem"<<std::endl;
    std::cout << vectorToString(message) << std::endl;


    // odnajdywanie bledu
    std::vector<bool> error;
    getErrorVector(message, error, H);

    std::cout << "syndrom bledu"<<std::endl;
    std::cout << vectorToString(error) << std::endl;

    fixDoubleError(message, error, H);
    std::cout << "poprawiona wiadomosc"<<std::endl;
    std::cout << vectorToString(message) << std::endl;
}
// todo: napisac metode ktora sprawdza suma ktrorych dwoch kolumn jest rowna error

/*void fixDoubleError(std::vector<bool>& message, const std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix ) {

    //zabezpieczenie, ze mnozenie jest mozliwe
    if (message.size() != hammingMatrix[0].size()) {
        std::cout << "Error message size doesn't match hamming matrix size" << std::endl;
        return;
    }

    //wybieramy piersza kolumne (firstCol), dodajemy z druga wybrana kolumna (secondCol), sprawdzamy czy error jest taki sam jak ta suma
    for (int firstCol = 0 ; firstCol<message.size(); firstCol++) {
        for (int secondCol = 0 ; secondCol<message.size(); secondCol++) {

            bool errorFound = true;

            //dodawanie firstCol i secondCol
            std::vector<bool> sumV;
            // error ma ten sam rozmiar jak columna
            sumV.reserve(error.size());
            for (int i = 0 ; i < error.size() ; i++) {
                sumV.push_back(hammingMatrix[firstCol][i] ^ hammingMatrix[secondCol][i]);
            }
            if (sumV ==  error) {
                // znalezlismy dwie kolumny w ktorych wystapily bledy
                std::cout<< "kolumny bledow"<< std::endl;
                std::cout << vectorToString(hammingMatrix[firstCol]) << "          "<<vectorToString(hammingMatrix[secondCol]) << std::endl;
            }

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