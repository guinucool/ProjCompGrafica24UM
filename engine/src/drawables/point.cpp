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

    /* Construtor de ponto através da leitura de uma configuração XML */
    Point::Point(tinyxml2::XMLElement * point) {
        this->read(point);
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

    /* Negação das coordenadas do ponto */
    void Point::negate() {

        /* Negação das coordenadas */
        this->x = -this->x;
        this->y = -this->y;
        this->z = -this->z;
    }

    /* Leitura de um ponto através de um ficheiro */
    void Point::read(std::ifstream& stream) {

        /* Leitura do valor das três coordenadas vindas de um ficheiro */
        stream.read(reinterpret_cast<char*>(&(this->x)), sizeof(float));
        stream.read(reinterpret_cast<char*>(&(this->y)), sizeof(float));
        stream.read(reinterpret_cast<char*>(&(this->z)), sizeof(float));

        /* Verfica se a leitura foi válida */
        if (stream.fail())
            throw std::invalid_argument("given 3d file is invalid");
    }

    /* Leitura de um ponto através de um formato XML */
    void Point::read(tinyxml2::XMLElement * point) {

        /* Verifica se a propriedade de ponto é válida */
        if (point->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Variáveis que irão armazenar os atributos */
        float x, y, z;

        /* Obtenção dos atributos e verificação da existência deles */
        if (point->QueryFloatAttribute("x", &x) || point->QueryFloatAttribute("y", &y) || point->QueryFloatAttribute("z", &z))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação das propriedades */
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /* Desenho de um ponto no modo imediato */
    void Point::draw() const {
        glVertex3f(this->x, this->y, this->z);
    }

    /* Alimentação de um buffer para desenho em modo VBO */
    void Point::feedBuffer(std::vector<float>& buffer) const {
        buffer.push_back(this->x);
        buffer.push_back(this->y);
        buffer.push_back(this->z);
    }

    /* Operação de clonagem de um ponto */
    Point Point::clone() const {
        return Point((*this));
    }
}