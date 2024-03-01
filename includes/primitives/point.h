#ifndef POINT_H
#define POINT_H

#include <fstream>
#include <string>

class Point {
private:
    float x, y, z;

public:
    Point();
    Point(float x, float y, float z);
    Point(const Point& point);
    Point(std::ifstream& stream);

    float getX() const;
    float getY() const;
    float getZ() const;

    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);

    void write(std::ofstream& stream) const;
    void read(std::ifstream& stream);

    Point rotateNew(float angleX, float angleY, float angleZ);
    Point translateNew(float dx, float dy, float dz);

    void draw() const;
    void feedBuffer(float* buffer);
    bool equals(const Point& other) const;
    Point clone() const;
    std::string toString() const;
};

#endif // POINT_H
