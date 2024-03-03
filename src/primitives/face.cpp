#include "../../includes/primitives/point.h"
#include <iostream>
#include <fstream>

/* Inicialização do namespace ao qual a classe pertence */
namespace primitives
{

    /* Definição do objeto tipo face */
    class Face {

        private:

            /* Definição dos três pontos que constituem uma face */
            Point first;
            Point second;
            Point third;

        public:

            /* Construtor parametrizado de três pontos */
            Face(Point first, Point second, Point third) {

            }

            /* Construtor de cópia */
            Face(const Face& face) {

            }

            /*  */
            Face() {

            }

            /* Destruição do objeto tipo face */
            ~Face();

            void setPoints(Point first, Point second, Point third) {

            }

            void setFirst(Point point) {

            }

            void setSecond(Point point) {
                
            }

            void setThird(Point point) {
                
            }

            Point getFirst() const {

            }

            Point getSecond() const {
                
            }

            Point getThird() const {
                
            }

            Face transform() const {

            }

            Face translateD(float dx, float dy, float dz) const {

            }

            Face translateR(float radius, float beta, float theta) const {

            }

            Face rotate(float angleX, float angleY, float angleZ) const {

            }
    };
}


class Face {
private:
    Point first, second, third;

public:

    Face(Point point0, Point point1, Point point2) : first(point0), second(point1), third(point2) {}

    Face(std::ifstream &fstream) {
        // TODO
    }

    Point getFirst() const { return first; }
    Point getSecond() const { return second; }
    Point getThird() const { return third; }

    void setFirst(Point point) { first = point; }
    void setSecond(Point point) { second = point; }
    void setThird(Point point) { third = point; }

    void write(std::ofstream &ofstream) const {
        // TODO
    }

    void read(std::ifstream &ifstream) {
        // TODO
    }

    Point rotateNew(float angleX, float angleY, float angleZ) {
        // TODO
    }

    Point translateNew(float x, float y, float z) {
        // TODO
    }

    Point rotateNew(float theta, float radius) {
        // TODO
    }

    void draw() const {
        // TODO
    }

    void feedBuffer(float* buffer) {
        // TODO
    }

    bool equals(Point point) const {
        // Implementação para verificar se algum dos pontos é igual ao fornecido
        return (first.getX() == point.getX() && first.getY() == point.getY() && first.getZ() == point.getZ()) ||
               (second.getX() == point.getX() && second.getY() == point.getY() && second.getZ() == point.getZ()) ||
               (third.getX() == point.getX() && third.getY() == point.getY() && third.getZ() == point.getZ());
    }

    Face clone() const {
        // Implementação para clonar a face
        return Face(first, second, third);
    }

    std::string toString() const {
        std::string result = "Face: ";
        result += "First: "; first.toString(); result += ", ";
        result += "Second: "; second.toString(); result += ", ";
        result += "Third: "; third.toString();
        return result;
    }
};