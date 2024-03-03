#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>
#include <stdexcept>

#include "../../includes/containers/world.hpp"
#include "../../includes/containers/window.hpp"
//#include "../../src/lib/tinyxml2.h"

//using namespace containers;

//#define T2 tinyxml2

class World {
private:
  
  containers::Window * window;
  //  Camera * camera;

public:

  World(std::string file)
  {
    window = new containers::Window(file);
  }
};
