#include <bitset>
#include <iostream>
#include <string>
#include <vector>

#include "./singleError/singleErrorDetection.h"
#include <cstdlib>  // Dla rand() i srand()
#include <ctime>    // Dla time()

bool isSumOfCol(const std::vector<int>& v, int i) {

    for (const auto it : v) {
        for (const auto jt : v) {
            if (it + jt == i) {
                return true;
            }
        }
    }

    return false;
}

std::vector<bool> intToBoolV (int x) {
    std::vector<bool> v;
    int i = 0;
    while (x || i<8) {
        v.push_back(x % 2);
        x /= 2;
        i++;
    }
    return v;
}

std::vector<std::vector<bool>> intVtoBoolV(std::vector<int>& v) {
    std::vector<std::vector<bool>> boolV;

    for (auto i : v) {
        boolV.push_back(intToBoolV(i));
    }

    return boolV;
}

bool allZeroInCol(std::vector<std::vector<bool>> V) {
    for (auto i : V) {
        for (auto j : i) {
            if (j != 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    // tablica bitow 8 bitow
    // std::vector<bool> message = {1,0,1,0,1,0,1,0};
    // singleErrorDetection(message);
    srand(static_cast<unsigned int>(time(0)));

    //szukamy macierzy gdzie zadna z kolumn nie jest suma innych kolumn. robimy bruteforce
    // std::vector<std::vector<bool>> matrix;
    std::vector<int> matrix;


    //wiersze w kolumanch maja zawierać liczby od 1 do 255
    // long long i = 0;
    // do{
    //     for (int i = rand() % 256 + 1; i<256 && matrix.size() < 17; ) {
    //         if (!isSumOfCol(matrix, i))
    //             matrix.push_back(i);
    //
    //         i = rand() % 256 + 1;
    //     }
    //     boolV = intVtoBoolV(matrix);
    //     // i++;
    //     // std::cout << i<<std::endl;;
    //     /*for (auto i: boolV) {
    //         std::cout << vectorToString(i)<<std::endl;
    //     }
    //     system("clear");*/
    // } while (!allZeroInCol(boolV));
    std::vector<std::vector<bool>> boolV ={
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0}
    }


    isSumOfCol(matrix, i);

    for (auto i: matrix) {
        std::cout << i << " ";
    }


    for (auto i: boolV) {
        std::cout << vectorToString(i)<<std::endl;
    }

    std::vector<std::vector<bool>> H ={
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    return 0;
}
