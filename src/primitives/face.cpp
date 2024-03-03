#include "../../includes/primitives/face.hpp"
#include "../../includes/primitives/point.hpp"
#include <iostream>
#include <fstream>

namespace primitives
{

    Face::Face(Point point0, Point point1, Point point2){
        this->first = point0;
        this->second = point1;
        this->third = point2;
    }

    Face::Face(std::ifstream &fstream) {
        // TODO
    }

    Point Face::getFirst() const { return this->first; }
    Point Face::getSecond() const { return this->second; }
    Point Face::getThird() const { return this->third; }

    void Face::setFirst(Point point) { this->first = point; }
    void Face::setSecond(Point point) { this->second = point; }
    void Face::setThird(Point point) { this->third = point; }

    void Face::write(std::ofstream &ofstream) const {
        // TODO
    }

    void Face::read(std::ifstream &ifstream) {
        // TODO
    }

    Face Face::rotateNew(float angleX, float angleY, float angleZ) {
        Point rotatedFirst = this->first.rotate(angleX, angleY, angleZ);
        Point rotatedSecond = this->second.rotate(angleX, angleY, angleZ);
        Point rotatedThird = this->third.rotate(angleX, angleY, angleZ);

    return Face(rotatedFirst, rotatedSecond, rotatedThird);
    }

    Point Face::translateD(float x, float y, float z) {
        Point translatedFirst = this->first.translateD(x, y, z);
        Point translatedSecond = this->second.translateD(x, y, z);
        Point translatedThird = this->third.translateD(x, y, z);

        return Face(translatedFirst, translatedSecond, translatedThird);
    }

    Point Face::translateP(float beta, float theta, float radius) {
        Point translatedFirst = this->first.translateP(radius, beta, theta);
        Point translatedSecond = this->second.translateP(radius, beta, theta);
        Point translatedThird = this->third.translateP(radius, beta, theta);

        return Face(translatedFirst, translatedSecond, translatedThird);
    }

    void Face::draw() const {
        // TODO
    }

    void Face::feedBuffer(float* buffer) {
    }

    bool Face::equals(Face face) const {
        return
            (this->first.equals(face.getFirst()) &&
            this->second.equals(face.getSecond()) &&
            this->third.equals(face.getThird())) || 
            (this->first.equals(face.getSecond()) &&
            this->second.equals(face.getThird()) &&
            this->third.equals(face.getFirst())) ||
            (this->first.equals(face.getThird()) &&
            this->second.equals(face.getFirst()) &&
            this->third.equals(face.getSecond()));
    }

    Face Face::clone() const {
        // Implementação para clonar a face
        return Face::Face(first, second, third);
    }

    std::string Face::toString() const {
        std::string result = "Face: ";
        result += "First: "; first.toString(); result += ", ";
        result += "Second: "; second.toString(); result += ", ";
        result += "Third: "; third.toString();
        return result;
    }
};
