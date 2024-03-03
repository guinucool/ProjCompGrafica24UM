#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <stdexcept>

#include "../../includes/containers/window.hpp"
#include "../../src/lib/tinyxml2.h"

#define T2 tinyxml2

namespace containers
{
  class Window {
  private:
    int width, height = 0;

  public:
    
    Window() : width(100), height(100) {}

    Window(int width, int height) : width(width), height(height) {}

    Window(const Window& window) : width(window.width), height(window.height) {}
  
    Window(std::string file)
    {
      static const char* f = file.c_str();
      T2::XMLDocument doc;
      doc.LoadFile(f);
      T2::XMLElement * window_elem = doc.RootElement()->FirstChildElement("window");

      int w, h = 0;
      window_elem->QueryIntAttribute("width", &w);
      window_elem->QueryIntAttribute("height", &h);
    
      width = w;
      height = h;
    }

    // Métodos de acesso
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void setWidth(int w) { width = w; }

    void setHeight(int h) { height = h; }
  };
};
