#include <vector>
#include <iostream>
#include <string>
#include "../includes/utils/matrix.hpp"

int main() {

    utils::Matrix man1(3, 3, 1.0f);
    utils::Matrix man2(3, 3, 2.0f);

    utils::Matrix man3 = man1 + man2;

    std::cout << man3.toString();
    return 0;
}