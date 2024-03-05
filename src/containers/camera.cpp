#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <stdexcept>

#include "../../includes/containers/camera.hpp"
#include "../../includes/primitives/point.hpp"
#include "../../src/lib/tinyxml2.h"

#define T2 tinyxml2

namespace containers
{
  class Camera {
  private:
    Point position, lookAt, up;
    float fov, near, far;

  public:
  
    Camera(std::string file)
    {
      static const char* f = file.c_str();
      T2::XMLDocument doc;
      doc.LoadFile(f);
      T2::XMLElement * camera_elem = doc.RootElement()->FirstChildElement("camera");

      T2::XMLElement * pos_elem = camera_elem->FirstChildElement("position");
      T2::XMLElement * loo_elem = camera_elem->FirstChildElement("lookAt");
      T2::XMLElement * up_elem = camera_elem->FirstChildElement("up");
      T2::XMLElement * pro_elem = camera_elem->FirstChildElement("projection");

      float x, y, z = 0.0f;

      pos_elem->QueryFloatAttribute("x", &x);
      pos_elem->QueryFloatAttribute("y", &y);
      pos_elem->QueryFloatAttribute("z", &z);
      this->position = * new Point(x, y, z);

      loo_elem->QueryFloatAttribute("x", &x);
      loo_elem->QueryFloatAttribute("y", &y);
      loo_elem->QueryFloatAttribute("z", &z);
      this->lookAt = * new Point(x, y, z);

      up_elem->QueryFloatAttribute("x", &x);
      up_elem->QueryFloatAttribute("y", &y);
      up_elem->QueryFloatAttribute("z", &z);
      this->up = * new Point(x, y, z);

      pro_elem->QueryFloatAttribute("fov", &fov);
      pro_elem->QueryFloatAttribute("near", &near);
      pro_elem->QueryFloatAttribute("far", &far);
    }

    // Métodos de acesso
    Point getPosition() const { return position; }
    Point getLookAt() const { return lookAt; }
    Point getUp() const { return up; }
    float getFov() const { return fov; }
    float getNear() const { return near; }
    float getFar() const { return far; }

    void setPosition(Point p) { position = p.clone(); }
    void setLookAt(Point p) { lookAt = p.clone(); }
    void setUp(Point p) { up = p.clone(); }
    void setFov(float f) { fov = f; }
    void setNear(float f) { near = f; }
    void setFar(float f) { far = f; }
  }; 
};
