#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>

#include "../../includes/primitives/point.hpp"

class Camera {
private:
  Point * position, lookAt, up, projection;

public:
  Camera();
  Camera(std::string file);

  Point getPosition() const;
  Point getLookAt() const;
  Point getUp() const;
  float getFov() const;
  float getNear() const;
  float getFar() const;

  void setPosition(Point p);
  void setLookAt(Point p);
  void setUp(Point p);
  void setFov(float f);
  void setNear(float f);
  void setFar(float f);

};

#endif // CAMERA_HPP
