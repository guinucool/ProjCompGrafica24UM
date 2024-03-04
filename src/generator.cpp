#include "../includes/primitives/point.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

int main() {

    primitives::Point ponto(0,0,1);

    ponto.rotate(0, M_PI / 2, 0);

    std::cout << ponto.toString() << std::endl;

    /*const utils::Matrix matrix(4, 4);

    std::cout << matrix[0] << std::endl;*/

    /*std::ofstream out("bin.b", std::ios::binary);

    int value = 10;
    int valu2 = 13;

    out.write(reinterpret_cast<const char*>(&value), sizeof(int));
    out.write(reinterpret_cast<const char*>(&valu2), sizeof(int));

    out.close();

    std::ifstream in("bin.b", std::ios::binary);

    int read;

    in.read(reinterpret_cast<char*>(&read), sizeof(int));

    std::cout << read << std::endl;

    in.read(reinterpret_cast<char*>(&read), sizeof(int));

    std::cout << read << std::endl;

    in.close();*/

    return 0;
}