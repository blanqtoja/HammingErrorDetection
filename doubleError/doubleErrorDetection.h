//
// Created by olek1 on 26/03/2025.
//

#ifndef DOUBLEERRORDETECTION_H
#define DOUBLEERRORDETECTION_H

#include <vector>
#include <iostream>
#include "../methods.h"

void doubleErrorDetection(std::vector<bool> message);
void encodeMessage(std::vector<bool>& message, const std::vector<std::vector<bool>>& hammingMatrix);
void getErrorVector(const std::vector<bool>& message, std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix );
void fixError(std::vector<bool>& message, const std::vector<bool>& error, const std::vector<std::vector<bool>>& hammingMatrix );


#endif //DOUBLEERRORDETECTION_H
