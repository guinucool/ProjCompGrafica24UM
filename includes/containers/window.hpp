#ifndef WINDOW_HPP
#define WINDOW_HPP

namespace containers {
    class Window {
    private:
      int width, height;

    public:
      Window();
      Window(int width, int height);
      Window(const Window& window);

      int getWidth() const;
      int getHeight() const;

      void setWidth(int w);
      void setHeight(int h);
    };
};

#endif // WINDOW_H
