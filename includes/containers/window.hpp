#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {
private:
  int width, height;

public:
  Window();
  Window(int width, int height);
  Window(const Window& window);
  Window(std::string file);

  int getWidth() const;
  int getHeight() const;

  void setWidth(int w);
  void setHeight(int h);
};


#endif // WINDOW_H
