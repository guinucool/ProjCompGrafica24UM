#include "../includes/models/plane.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

void some(std::vector<int>& vector) {
    vector.push_back(10);
}

int main() {

    models::Plane plane(1, 3);

    std::cout << plane.toString();

    /*std::vector<int> vector(10, 1);

    for (int i = 0; i < vector.size(); i++)
        std::cout << vector[i] << std::endl;

    some(vector);

    for (int i = 0; i < vector.size(); i++)
        std::cout << vector[i] << std::endl;*/
    

    /*float x = 0.0f;
    float y = 1.0f;

    const char * coisa = reinterpret_cast<const char*>(&y);
    const float * coisa2 = reinterpret_cast<const float*>(coisa);

    std::cout << (*coisa2) << std::endl;*/

    //std::ifstream out("bin.3d", std::ios::binary);

    //primitives::Face face(out);

    //face.translateD(10, 0, 1);

    //std::cout << face.toString() << std::endl;

    //out.close();

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