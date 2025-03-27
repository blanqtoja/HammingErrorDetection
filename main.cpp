#include <bitset>
#include <iostream>
#include <string>
#include <vector>

#include "./singleError/singleErrorDetection.h"
#include "./doubleError/doubleErrorDetection.h"

int main() {

    std::vector<bool> messange = { 1,0,1,0,1,0,1,0};
    doubleErrorDetection(messange);

    return 0;
}
