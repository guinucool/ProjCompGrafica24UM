#ifndef FACE_HPP
#define FACE_HPP

#include "point.hpp"
#include <fstream>
#include <string>

namespace primitives{

    class Face {
        
    private:
        Point first, second, third;

    public:
        Face(Point point0, Point point1, Point point2);
        Face(std::ifstream &fstream);

        Point getFirst() const;
        Point getSecond() const;
        Point getThird() const;

        void setFirst(Point point);
        void setSecond(Point point);
        void setThird(Point point);

        void write(std::ofstream &ofstream) const;
        void read(std::ifstream &ifstream);

        Face rotateNew(float angleX, float angleY, float angleZ);
        Point translateD(float x, float y, float z);
        Point translateP(float theta, float radius);

        void draw() const;
        void feedBuffer(float* buffer);
        
        bool equals(Face face) const;
        Face clone() const;
        std::string toString() const;
    };
}
#endif // FACE_H
