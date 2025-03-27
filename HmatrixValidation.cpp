//
// Created by olek1 on 27/03/2025.
//

#include "HmatrixValidation.h"

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