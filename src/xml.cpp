#include "../external/tinyxml2/tinyxml2.h"
#include <iostream>

int main() {

    tinyxml2::XMLDocument test;
    test.LoadFile("teste.xml");

    tinyxml2::XMLElement * world = test.FirstChildElement("world");

    if (world != NULL)
    {
        std::cout << "YO!" << std::endl;

        tinyxml2::XMLElement * next = world->FirstChildElement();

        float x = 10;

        std::cout << next->Value() << std::endl;
        std::cout << next->QueryFloatAttribute("widthA", &x) << std::endl;
        std::cout << std::to_string(x) << std::endl;
        world->DeleteChild(next);

        tinyxml2::XMLNode * next1 = world->FirstChild();
        std::cout << next1->Value() << std::endl;
        
    }
}