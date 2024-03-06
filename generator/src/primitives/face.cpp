/* Inclusão do cabeçalho de definição da estrutura de face */
#include "../../inc/primitives/face.hpp"

/* Inclusão de pacotes necessários ao funcionamento do módulo */
#include <iostream>
#include <fstream>

/* Inicialização do namespace ao qual a classe pertence */
namespace primitives
{
    /* Construtor parametrizado de pontos com ordem */
    Face::Face(Point first, Point second, Point third) {
        this->setPoints(first, second, third);
    }

    /* Construtor de cópia de face */
    Face::Face(const Face& face) : first(face.first), second(face.second), third(face.third) {}

    /* Construtor de face através de um ficheiro */
    Face::Face(std::ifstream& stream) {
        this->read(stream);
    }

    /* Definição do primeiro ponto da face */
    void Face::setFirst(Point point) {

        /* Verifica se todos os pontos são compatíveis */
        if (point == this->second || point == this->third)
            std::runtime_error("incompatible face points");

        /* Associação do ponto */
        this->first = point;
    }

    /* Definição do segundo ponto da face */
    void Face::setSecond(Point point) {

        /* Verifica se todos os pontos são compatíveis */
        if (point == this->first || point == this->third)
            std::runtime_error("incompatible face points");

        /* Associação do ponto */
        this->second = point;
    }

    /* Definição do terceiro ponto da face */
    void Face::setThird(Point point) {

        /* Verifica se todos os pontos são compatíveis */
        if (point == this->first || point == this->second)
            std::runtime_error("incompatible face points");

        /* Associação do ponto */
        this->third = point;
    }

    /* Definição de todos os pontos da face */
    void Face::setPoints(Point first, Point second, Point third) {
         
        /* Verifica se todos os pontos são compatíveis */
        if (first == second || second == third || third == first)
            std::runtime_error("incompatible face points");

        /* Definição dos pontos */
        this->first = first;
        this->second = second;
        this->third = third;
    }

    /* Devolução do primeiro ponto da face */
    Point Face::getFirst() const {
        return this->first;
    }

    /* Devolução do segundo ponto da face */
    Point Face::getSecond() const {
        return this->second;
    }

    /* Devolução do terceiro ponto da face */
    Point Face::getThird() const {
        return this->third;
    }

    /* Transformação de uma face dada uma matriz */
    void Face::transform(const utils::Matrix& transform) {

        /* Aplicação da matriz aos três pontos */
        this->first.transform(transform);
        this->second.transform(transform);
        this->third.transform(transform);
    }

    /* Translação de uma face dado um vetor */
    void Face::translateD(float dx, float dy, float dz) {

        /* Criação da matriz de translação */
        utils::Matrix translate = utils::Matrix::translateD(dx, dy, dz);

        /* Aplicação da matriz */
        this->transform(translate);
    }

    /* Translação de uma face dado um vetor polar */
    void Face::translateP(float radius, float alpha, float beta) {

        /* Criação da matriz de translação */
        utils::Matrix translate = utils::Matrix::translateP(radius, alpha, beta);

        /* Aplicação da matriz */
        this->transform(translate);
    }

    /* Rotação de uma face dado o ângulo de rotação sobre cada eixo */
    void Face::rotate(float ax, float ay, float az) {

        /* Criação das matrizes de rotação */
        utils::Matrix rotateX = utils::Matrix::rotateX(ax);
        utils::Matrix rotateY = utils::Matrix::rotateY(ay);
        utils::Matrix rotateZ = utils::Matrix::rotateZ(az);

        /* Aplicação da matriz */
        this->transform(rotateX * rotateY * rotateZ);
    }

    /* Rotação de uma face para ficar virada para o lado oposto */
    void Face::turn() {

        /* Armazenador auxiliar */
        Point aux = this->first;

        /* Troca de pontos */
        this->first = this->third;
        this->third = aux;
    }

    /* Escrita de uma face em ficheiro */
    void Face::write(std::ofstream &stream) const {
        
        /* Escrita do valor dos três pontos em ficheiro */
        this->first.write(stream);
        this->second.write(stream);
        this->third.write(stream);
    }

    /* Leitura de uma face através de um ficheiro */
    void Face::read(std::ifstream &stream) {
        
        /* Leitura do valor dos três pontos vindos de um ficheiro */
        this->first.read(stream);
        this->second.read(stream);
        this->third.read(stream);
    }

    /* Desenho de uma face no modo imediato */
    void Face::draw() const {
        // TODO
    }

    /* Alimentação de um buffer para desenho em modo VBO */
    void Face::feedBuffer(std::vector<float>& buffer) const {
        // TODO
    }

    /* Operação de comparação por igualdade de faces */
    bool Face::operator==(const Face& face) const {
        return (this->first == face.first && this->second == face.second && this->third == face.third) ||
               (this->first == face.second && this->second == face.third && this->third == face.first) ||
               (this->first == face.third && this->second == face.first && this->third == face.second);
    }

    /* Operação de comparação por desigualdade de faces */
    bool Face::operator!=(const Face& face) const {
        return !((this->first == face.first && this->second == face.second && this->third == face.third) ||
                 (this->first == face.second && this->second == face.third && this->third == face.first) ||
                 (this->first == face.third && this->second == face.first && this->third == face.second));
    }

    /* Operação de clonagem de uma face */
    Face Face::clone() const {
        return Face((*this));
    }

    /* Transformação de uma face em string */
    std::string Face::toString() const {

        /* Criação da string vazia */
        std::string result = "";

        /* Construção da string que irá representar a face */
        result += "1-" + first.toString() + '\n';
        result += "2-" + second.toString() + '\n';
        result += "3-" + third.toString();

        /* Devolução da string construída */
        return result;
    }
};
