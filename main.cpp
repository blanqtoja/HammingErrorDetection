#include <iostream>
#include <string>


bool getBit(uint8_t value, int bitIndex) {
    return (value & (1 << bitIndex)) != 0;
}

void setBit(uint8_t &value, int bitIndex) {
    value |= (1 << bitIndex);
}

void clearBit(uint8_t &value, int bitIndex) {
    value &= ~(1 << bitIndex);
}

int main() {

    //korekcja jednego bledu
    //    2^k >= m+k+1

    // tablica bitow 8 bitow
    uint8_t meesage = 0b10101010;

    // dwuwymiarowa tablica bitow (k x m+k) => (4x12)
    uint8_t H_c4[4][12] = {
          // 0  1  2  3  4  5  6  7  8  9  10 11
            {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
            {0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0},
            {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1}
    };

    uint8_t c1 = getBit(meesage, 0) ^ getBit(meesage, 2) ^ getBit(meesage, 5) ^ getBit(meesage, 7) ^ getBit(meesage, 9);
    uint8_t c2 = getBit(meesage, 1) ^ getBit(meesage, 3) ^ getBit(meesage, 6) ^ getBit(meesage, 7);
    uint8_t c3 = getBit(meesage, 0) ^ getBit(meesage, 1) ^ getBit(meesage, 2) ^ getBit(meesage, 3) ^ getBit(meesage, 5);
    uint8_t c4 = getBit(meesage, 2) ^ getBit(meesage, 3) ^ getBit(meesage, 4) ^ getBit(meesage, 5) ^ getBit(meesage, 6) ^ getBit(meesage, 7);

    bool error = c1 ^ c2 ^ c3 ^ c4;

    if(error) {
        // znajdz kolumne z bledem
        uint8_t errorColumn = c1 * 1 + c2 * 2 + c3 * 4 + c4 * 8;
        std::cout<< "Error in column: " << errorColumn << "\n";
        std::cout<< "Incorrect message: " << std::to_string(meesage) << "\n";
        // zmien bit w kolumnie
        meesage ^= (1 << errorColumn);
        std::cout<< "Corrected message: " << std::to_string(meesage) << "\n";
    } else {
        // nie ma bledu


    }

    // zacierz matrix transponowana
//    uint8_t matrixT[12][4] = {
//            {1, 0, 1, 0},
//            {0, 1, 1, 0},
//            {1, 0, 1, 1},
//            {0, 1, 1, 1},
//            {1, 0, 0, 1},
//            {0, 0, 1, 1},
//            {1, 1, 0, 1},
//            {0, 1, 0, 1},
//            {1, 0, 0, 0},
//            {0, 1, 0, 0},
//            {0, 0, 1, 0},
//            {0, 0, 0, 1}
//    };



    return 0;
}
