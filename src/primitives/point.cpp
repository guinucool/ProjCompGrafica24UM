/* Inclusão do cabeçalho de definição da classe */
#include "../../includes/primitives/point.hpp"

/* Inclusão de livrarias necessárias à funcionalidade */
#include <stdexcept>
#include <cmath>

/* Inicialização do namespace ao qual a classe pertence */
namespace primitives
{
    /* Definição do valor das coordenadas de um ponto */
    void Point::setCoords(float x, float y, float z) {

        /* Associação das coordendas à respetiva posição no vetor */
        this->X() = x;
        this->Y() = y;
        this->Z() = z;
    }

    /* Construtor vazio que invoca um ponto sempre na origem do referencial */
    Point::Point() : coords(4, 1, 1.0f) {

        /* Associação de coordenadas */
        this->setCoords(0.0f, 0.0f, 0.0f);
    }

    /* Construtor parametrizado */
    Point::Point(float x, float y, float z) : coords(4, 1, 1.0f) {

        /* Associação das coordenadas */
        this->setCoords(x, y, z);
    }

    /* Construtor de cópia */
    Point::Point(const Point& point) : coords(4, 1, 1.0f) {

        /* Associação das coordenadas */
        this->setCoords(point.X(), point.Y(), point.Z());
    }

    /* Construtor de ponto através de um ficheiro */
    Point::Point(std::ifstream& stream) : coords(4, 1, 1.0f) {

        /* Leitura do ponto através do ficheiro */
        this->read(stream);
    }

    /* Construtor parametrizado de ponto para coordenadas polares */
    Point Point::polarPoint(float radius, float alpha, float beta) {

        /* Tradução das coordenadas */
        float x = radius * cos(beta) * sin(alpha);
        float y = radius * cos(beta) * cos(alpha);
        float z = radius * sin(beta);

        /* Criação do ponto polar */
        return Point(x, y, z);
    }

    /* Devolução da referência do valor da coordenada x do ponto */
    float& Point::X() {
        return this->coords[0];
    }

    /* Devolução da referência do valor da coordenada x do ponto sem possibilidade de alteração */
    const float& Point::X() const {
        return this->coords[0];
    }

    /* Devolução da referência do do valor da coordenada y do ponto */
    float& Point::Y() {
        return this->coords[1];
    }

    /* Devolução da referência do valor da coordenada y do ponto sem possibilidade de alteração */
    const float& Point::Y() const {
        return this->coords[1];
    }

    /* Devolução da referência do do valor da coordenada z do ponto */
    float& Point::Z() {
        return this->coords[2];
    }

    /* Devolução da referência do valor da coordenada z do ponto sem possibilidade de alteração */
    const float& Point::Z() const {
        return this->coords[2];
    }

    /* Devolução da matriz das coordenadas do ponto */
    utils::Matrix Point::getCoords() const {
        return utils::Matrix(this->coords);
    }

    /* Transformação de um ponto dada uma matriz */
    void Point::transform(const utils::Matrix& transform) {

        /* Verifica se a matriz de transformação é compatível */
        if (transform.getRows() != 4 && transform.getCols() != 4)
            throw std::runtime_error("matrix invalid for transform");

        /* Criação das novas coordenadas do ponto */
        this->coords = transform * this->coords;
    }

    /* Translação de um ponto dado um vetor */
    void Point::translateD(float dx, float dy, float dz) {

        /* Criação da matriz de translação */
        utils::Matrix translate = utils::Matrix::translateD(dx, dy, dz);

        /* Aplicação da matriz */
        this->transform(translate);
    }

    /* Translação de um ponto dado um vetor polar */
    void Point::translateP(float radius, float alpha, float beta) {

        /* Criação da matriz de translação */
        utils::Matrix translate = utils::Matrix::translateP(radius, alpha, beta);

        /* Aplicação da matriz */
        this->transform(translate);
    }

    /* Rotação de um ponto dado o ângulo de rotação sobre cada eixo */
    void Point::rotate(float ax, float ay, float az) {

        /* Criação das matrizes de rotação */
        utils::Matrix rotateX = utils::Matrix::rotateX(ax);
        utils::Matrix rotateY = utils::Matrix::rotateY(ay);
        utils::Matrix rotateZ = utils::Matrix::rotateZ(az);

        /* Aplicação da matriz */
        this->transform(rotateX * rotateY * rotateZ);
    }

    /* Escrita de um ponto em ficheiro */
    void Point::write(std::ofstream& stream) const {

        /* Escrita do valor das três coordenadas em ficheiro */
        stream.write(reinterpret_cast<const char*>(&(this->X())), sizeof(float));
        stream.write(reinterpret_cast<const char*>(&(this->Y())), sizeof(float));
        stream.write(reinterpret_cast<const char*>(&(this->Z())), sizeof(float));
    }

    /* Leitura de um ponto através de um ficheiro */
    void Point::read(std::ifstream& stream) {

        /* Leitura do valor das três coordenadas vindas de um ficheiro */
        stream.read(reinterpret_cast<char*>(&(this->X())), sizeof(float));
        stream.read(reinterpret_cast<char*>(&(this->Y())), sizeof(float));
        stream.read(reinterpret_cast<char*>(&(this->Z())), sizeof(float));
    }

    /* Desenho de um ponto no modo imediato */
    void Point::draw() const {

    }

    /* Alimentação de um buffer para desenho em modo VBO */
    void Point::feedBuffer(std::vector<float> buffer) const {

    }

    /* Operação de comparação por igualdade de pontos */
    bool Point::operator==(const Point& point) const {
        return this->coords == point.coords;
    }

    /* Operação de comparação por desigualdade de pontos */
    bool Point::operator!=(const Point& point) const {
        return this->coords != point.coords;
    }

    /* Operação de clonagem de um ponto */
    Point Point::clone() const {
        return Point((*this));
    }

    /* Transformação de um ponto em formato string */
    std::string Point::toString() const {

        /* Inicialização da string vazia */
        std::string point = "";

        /* Construção da string que irá representar o ponto */
        point = "(" + std::to_string(this->X()) + "," + std::to_string(this->Y()) + "," + std::to_string(this->Z()) + ")";

        /* Devolução da string criada */
        return point;
    }
}