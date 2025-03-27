//
// Created by olek1 on 27/03/2025.
//

#ifndef HMATRIXVALIDATION_H
#define HMATRIXVALIDATION_H

#include <vector>

bool isSumOfCol(const std::vector<int>& v, int i);
std::vector<bool> intToBoolV (int x) ;
std::vector<std::vector<bool>> intVtoBoolV(std::vector<int>& v);
bool allZeroInCol(std::vector<std::vector<bool>> V);


#endif //HMATRIXVALIDATION_H
