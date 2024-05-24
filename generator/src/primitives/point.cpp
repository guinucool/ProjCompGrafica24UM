/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/primitives/point.hpp"

/* Inclusão de livrarias necessárias à funcionalidade */
#include <stdexcept>
#include <cmath>
#include <iostream>

/* Inicialização do namespace ao qual a classe pertence */
namespace primitives
{
    /* Construtor vazio que invoca um ponto sempre na origem do referencial */
    Point::Point() : coords(4, 1, 1.0f), normal(4, 1, 0.0f) {

        /* Associação de coordenadas */
        this->setCoords(0.0f, 0.0f, 0.0f);
    }

    /* Construtor parametrizado */
    Point::Point(float x, float y, float z) : coords(4, 1, 1.0f), normal(4, 1, 0.0f) {

        /* Associação das coordenadas */
        this->setCoords(x, y, z);
    }

    /* Construtor de cópia */
    Point::Point(const Point& point) : coords(4, 1, 1.0f), normal(point.normal) {

        /* Associação das coordenadas */
        this->setCoords(point.X(), point.Y(), point.Z());
    }

    /* Construtor de um ponto vindo de um ficheiro */
    Point::Point(std::ifstream& stream) : coords(4, 1, 1.0f), normal(4, 1, 0.0f) {
        
        /* Leitura do ponto vindo do ficheiro */
        this->read(stream);
    }

    /* Construtor parametrizado de ponto para coordenadas polares */
    Point Point::polarPoint(float radius, float alpha, float beta) {

        /* Inicialização do ponto onde vão ser armazenadas as coordenadas */
        Point point;

        /* Associação das coordenadas polares */
        point.setPolarCoords(radius, alpha, beta);

        /* Devolução do ponto polar */
        return point;
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

    /* Definição do vetor normal de um ponto */
    void Point::setNormal(const utils::Matrix& normal) {

        /* Verifica se a matriz dada pode ser uma normal */
        if (normal.getRows() != 4 || normal.getCols() != 1 || normal[3] != 0)
            throw std::runtime_error("invalid normal vector given");

        /* Associação da normal */
        this->normal = normal;
    }

    /* Atualização do vetor normal de um ponto */
    void Point::updateNormal(const utils::Matrix& normal) {

        /* Verifica se a matriz dada pode ser uma normal */
        if (normal.getRows() != 4 || normal.getCols() != 1 || normal[3] != 0)
            throw std::runtime_error("invalid normal vector given");

        /* Atualização da normal atual com a nova */
        this->normal = (this->normal + normal).normalize();
    }

    /* Cálculo da normal para uma esfera */
    void Point::sphereNormal() {

        /* Atualização da normal para as coordenadas do ponto */
        this->normal[0] = this->X();
        this->normal[1] = this->Y();
        this->normal[2] = this->Z();

        /* Normalização da normal */
        this->normal = this->normal.normalize();
    }

    /* Devolução da matriz da normal do ponto */
    utils::Matrix Point::getNormal() const {
        return utils::Matrix(this->normal);
    }

    /* Normalização de um ponto para encaixar no espaço certo */
    void Point::normalize() {

        /* Obtenção do divisor para normalizar o ponto */
        float normalizer = this->coords[3];

        /* Divisão de todas as coordenadas pelo normalizador */
        for (size_t i = 0; i < 4; i++)
            this->coords[i] /= normalizer;
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
    void Point::rotate(float angle, float rx, float ry, float rz) {

        /* Criação da matriz de rotação */
        utils::Matrix rotate = utils::Matrix::rotate(angle, rx, ry, rz);

        /* Aplicação da matriz */
        this->transform(rotate);
    }

    /* Escala de um ponto dado um vetor de escala */
    void Point::scale(float sx, float sy, float sz) {

        /* Criação da matriz de escala */
        utils::Matrix scale = utils::Matrix::scale(sx, sy, sz);

        /* Aplicação da matriz */
        this->transform(scale);
    }

    /* Leitura de um ponto vindo de um ficheiro */
    void Point::read(std::ifstream& stream) {

        /* Atribuição do valor lido à coordenada */
        stream >> this->X();

        /* Ignora a vírgula que separa os valores */
        stream.ignore(1);

        /* Atribuição do valor lido à coordenada */
        stream >> this->Y();

        /* Ignora a vírgula que separa os valores */
        stream.ignore(1);

        /* Atribuição do valor lido à coordenada */
        stream >> this->Z();

        /* Verfica se a leitura foi válida */
        if (stream.fail())
            throw std::invalid_argument("given patch file is invalid");
    }

    /* Escrita de um ponto em ficheiro */
    void Point::write(std::ofstream& stream) const {

        /* Escrita do valor das três coordenadas em ficheiro */
        stream.write(reinterpret_cast<const char*>(&(this->X())), sizeof(float));
        stream.write(reinterpret_cast<const char*>(&(this->Y())), sizeof(float));
        stream.write(reinterpret_cast<const char*>(&(this->Z())), sizeof(float));

        /* Escrita do valor do vetor normal em ficheiro */
        stream.write(reinterpret_cast<const char*>(&(this->normal[0])), sizeof(float));
        stream.write(reinterpret_cast<const char*>(&(this->normal[1])), sizeof(float));
        stream.write(reinterpret_cast<const char*>(&(this->normal[2])), sizeof(float));

        /* Verifica se a escrita foi bem sucedida */
        if (stream.fail())
            std::runtime_error("failed to write to file");
    }

    /* Operação de clonagem de um ponto */
    Point Point::clone() const {
        return Point((*this));
    }

    /* Transformação de um ponto em formato string para ser usado como chave */
    std::string Point::stringKey() const {
        return geometry::Point::toString();
    }

    /* Transformação de um ponto em formato string */
    std::string Point::toString() const {

        /* Inicialização da string vazia */
        std::string point = geometry::Point::toString() + "\n";

        /* Construção da string que irá representar o ponto */
        point += "Normal:(" + std::to_string(this->normal[0]) + "," + std::to_string(this->normal[1]) + "," + std::to_string(this->normal[2]) + ")";

        /* Devolução da string criada */
        return point;
    }
}