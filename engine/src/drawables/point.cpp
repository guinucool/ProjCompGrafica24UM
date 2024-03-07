/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/drawables/point.hpp"

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>
#include <cmath>

/* Inicialização do namespace ao qual a classe pertence */
namespace drawables
{

    /* Construtor vazio que invoca um ponto sempre na origem do referencial */
    Point::Point() : x(0.0f), y(0.0f), z(0.0f) {}

    /* Construtor parametrizado de ponto */
    Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

    /* Construtor de cópia */
    Point::Point(const Point& point) : x(point.x), y(point.y), z(point.z) {}

    /* Construtor de ponto através da leitura do ficheiro */
    Point::Point(std::ifstream& stream) {
        this->read(stream);
    }

    /* Construtor parametrizado de ponto para coordenadas polares */
    Point Point::polarPoint(float radius, float alpha, float beta) {

        /* Inicialização do ponto ao qual vão ser atribuídas as coordenadas polares */
        Point point;

        /* Definição das coordenadas */
        point.setPolarCoords(radius, alpha, beta);

        /* Devolução do ponto polar */
        return point;
    }

    /* Devolução da referência do valor da coordenada x do ponto */
    float& Point::X() {
        return this->x;
    }

    /* Devolução da referência do valor da coordenada x do ponto sem possibilidade de alteração */
    const float& Point::X() const {
        return this->x;
    }

    /* Devolução da referência do valor da coordenada y do ponto */
    float& Point::Y() {
        return this->y;
    }

    /* Devolução da referência do valor da coordenada y do ponto sem possibilidade de alteração */
    const float& Point::Y() const {
        return this->y;
    }

    /* Devolução da referência do valor da coordenada z do ponto */
    float& Point::Z() {
        return this->z;
    }

    /* Devolução da referência do valor da coordenada z do ponto sem possibilidade de alteração */
    const float& Point::Z() const {
        return this->z;
    }

    /* Definição das coordenadas do ponto */
    void Point::setCoords(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /* Definição das coordenadas polares do ponto */
    void Point::setPolarCoords(float radius, float alpha, float beta) {

        /* Verifica a validade do raio */
        if (radius < 0)
            throw std::invalid_argument("given radius is invalid");

        /* Tradução e definição das coordenadas */
        this->x = radius * cos(beta) * sin(alpha);;
        this->y = radius * cos(beta) * cos(alpha);
        this->z = radius * sin(beta);
    }

    /* Leitura de um ponto através de um ficheiro */
    void Point::read(std::ifstream& stream) {

        /* Variável de verificação da validade da leitura */
        bool read = false;

        /* Leitura do valor das três coordenadas vindas de um ficheiro */
        read |= stream.read(reinterpret_cast<char*>(&(this->x)), sizeof(float)).fail();
        read |= stream.read(reinterpret_cast<char*>(&(this->y)), sizeof(float)).fail();
        read |= stream.read(reinterpret_cast<char*>(&(this->z)), sizeof(float)).fail();

        /* Verfica se a leitura foi válida */
        if (read)
            throw std::invalid_argument("given 3d file is invalid");        
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