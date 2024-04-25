#include <fstream>
#include <iostream>

int main() {

    std::ifstream stream("teapot.patch");
    int len;
    char comma;

    stream >> len;

    for (int i = 0; i < 32; i++)
    {
        stream >> len;

        /*if ((i + 1) % 16 != 0)
            stream.ignore(1);*/

        std::cout << len << " " << stream.fail() << std::endl;/* code */
    }
}