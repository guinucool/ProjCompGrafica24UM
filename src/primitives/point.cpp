#include "../../includes/primitives/point.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

class Point {
private:
    float x, y, z;

public:
    
    Point() : x(0.0f), y(0.0f), z(0.0f) {}

    Point(float x, float y, float z) : x(x), y(y), z(z) {}

    Point(const Point& point) : x(point.x), y(point.y), z(point.z) {}

    Point(std::ifstream& stream) {
        stream >> x >> y >> z;
    }

    // Métodos de acesso
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setZ(float newZ) { z = newZ; }

    // Operações de leitura e escrita em arquivos
    void write(std::ofstream& stream) const {
        stream << x << " " << y << " " << z << std::endl;
    }

    void read(std::ifstream& stream) {
        stream >> x >> y >> z;
    }

    // Transformações
    Point rotateNew(float angleX, float angleY, float angleZ) {
        // TODO
    }

    Point translateNew(float dx, float dy, float dz) {
        // TODO
    }

    void draw() const {
        // TODO
    }

    void feedBuffer(float* buffer) {
        // TODO
    }

    bool equals(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    Point clone() const {
        return Point(*this);
    }

    std::string toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }
};