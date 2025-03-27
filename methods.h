//
// Created by olek1 on 26/03/2025.
//

#ifndef METHODS_H
#define METHODS_H

#include <vector>
#include <string>

bool getParity(const std::vector<bool>& message, const std::vector<std::vector<bool>>& hammingMatrix, uint8_t row);
std::string vectorToString(const std::vector<bool>& message);
void encodeMessage(std::vector<bool>& message, const std::vector<std::vector<bool>>& hammingMatrix);
void getErrorVector(const std::vector<bool>& message, std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix );
void fixError(std::vector<bool>& message, const std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix );



#endif //METHODS_H
