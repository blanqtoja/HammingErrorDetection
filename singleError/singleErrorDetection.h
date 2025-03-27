//
// Created by olek1 on 26/03/2025.
//

#ifndef SINGLEERRORDETECTION_H
#define SINGLEERRORDETECTION_H

#include "../methods.h"

std::vector<bool> singleErrorDetection(std::vector<bool> message, const std::vector<std::vector<bool>>& hammingMatrix);
// void encodeMessage(std::vector<bool>& message, const std::vector<std::vector<bool>>& hammingMatrix);
// void getErrorVector(const std::vector<bool>& message, std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix );
void fixSingleError(std::vector<bool>& message, const std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix );

#endif //SINGLEERRORDETECTION_H
