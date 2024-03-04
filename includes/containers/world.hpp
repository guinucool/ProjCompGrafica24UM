#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>

#include "../../includes/containers/window.hpp"
#include "../../includes/containers/camera.hpp"

class World {

private:
  Window window;
  Camera camera;
      
public:

  World(std::string file);
};

#endif // WORLD_HPP
