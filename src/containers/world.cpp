#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>
#include <stdexcept>

#include "../../includes/containers/world.hpp"
#include "../../includes/containers/window.hpp"
#include "../../includes/containers/camera.hpp"
//#include "../../src/lib/tinyxml2.h"

//using namespace containers;

//#define T2 tinyxml2

namespace containers
{
  class World {
  private:
  
    Window window;
    Camera camera;

  public:

    World(std::string file)
    {
      window = * new Window(file);
      camera = * new Camera(file);
    }
  };
};
