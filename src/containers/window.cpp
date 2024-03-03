#include "../../includes/containers/window.hpp"
#include "../../src/lib/tinyxml2.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <stdexcept>

class Window {
private:
    int width, height = 0;

public:
    
  Window() : width(100), height(100) {}

  Window(int width, int height) : width(width), height(height) {}

  Window(const Window& window) : width(window.width), height(window.height) {}

    // Métodos de acesso
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void setWidth(int w) { width = w; }

  void setHeight(int h) { height = h; }
};
