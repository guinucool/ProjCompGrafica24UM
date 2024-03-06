/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/drawables/point.hpp"

/* Inclusão de módulos necessários à funcionalidade */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inicialização do namespace ao qual a classe pertence */
namespace drawables
{

    /* Construtor vazio que invoca um ponto sempre na origem do referencial */
    Point::Point() : x(0.0f), y(0.0f), z(0.0f) {}

    /* Construtor de cópia */
    Point::Point(const Point& point) : x(point.x), y(point.y), z(point.z) {}

    /* Construtor de ponto através da leitura do ficheiro */
    Point::Point(std::ifstream& stream) {
        this->read(stream);
    }

    /* Devolução da referência do valor da coordenada x do ponto sem possibilidade de alteração */
    const float& Point::X() const {
        return this->x;
    }

    /* Devolução da referência do valor da coordenada y do ponto sem possibilidade de alteração */
    const float& Point::Y() const {
        return this->y;
    }

    /* Devolução da referência do valor da coordenada z do ponto sem possibilidade de alteração */
    const float& Point::Z() const {
        return this->z;
    }

    /* Leitura de um ponto através de um ficheiro */
    void Point::read(std::ifstream& stream) {

        /* Leitura do valor das três coordenadas vindas de um ficheiro */
        stream.read(reinterpret_cast<char*>(&(this->x)), sizeof(float));
        stream.read(reinterpret_cast<char*>(&(this->y)), sizeof(float));
        stream.read(reinterpret_cast<char*>(&(this->z)), sizeof(float));
    }

    /* Desenho de um ponto no modo imediato */
    void Point::draw() const {
        glVertex3f(this->x, this->y, this->z);
    }

    /* Alimentação de um buffer para desenho em modo VBO */
    void Point::feedBuffer(std::vector<float>& buffer) const {

    }

    /* Operação de clonagem de um ponto */
    Point Point::clone() const {
        return Point((*this));
    }
}