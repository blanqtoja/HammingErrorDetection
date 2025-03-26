//
// Created by olek1 on 26/03/2025.
//

#include "methods.h"

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
