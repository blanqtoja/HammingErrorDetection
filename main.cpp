#include <bitset>
#include <iostream>
#include <string>
#include <vector>

#include "./singleError/singleErrorDetection.h"

int main() {



    // tablica bitow 8 bitow
    std::vector<bool> message = {1,0,1,0,1,0,1,0};
    singleErrorDetection(message);

    return 0;
}
