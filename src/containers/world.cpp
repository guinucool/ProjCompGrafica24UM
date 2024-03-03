#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>
#include <stdexcept>

#include "../../includes/containers/world.hpp"
#include "../../includes/containers/window.hpp"
#include "../../src/lib/tinyxml2.h"

//using namespace containers;

#define T2 tinyxml2

class World {
private:
  
  Window * window;
  //  Camera * camera;

public:

  World(std::string file)
  {
    static const char* f = file.c_str();
    T2::XMLDocument doc;
    doc.LoadFile(file.c_str());
    T2::XMLElement * w = doc.RootElement()->FirstChildElement("window");
    T2::XMLElement * c = doc.RootElement()->FirstChildElement("window");

    int width, height = 0;
    w->QueryIntAttribute("width", &width);
    w->QueryIntAttribute("height", &height);

    containers::Window * window = new containers::Window(width, height);
  }
};

int main() {
  World * w = new World("../../../xmlt/xml.xml");
    }
