//
// Created by olek1 on 26/03/2025.
//

#ifndef METHODS_H
#define METHODS_H

#include <vector>
#include <string>

bool getParity(const std::vector<bool>& message, const std::vector<std::vector<bool>>& hammingMatrix, uint8_t row);
std::string vectorToString(const std::vector<bool>& message);

#endif //METHODS_H
