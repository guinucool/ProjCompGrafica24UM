/* Inclusão do cabeçalho de definição da estrutura de face */
#include "../../inc/primitives/face.hpp"

/* Inclusão de livrarias necessárias à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace ao qual a classe pertence */
namespace primitives
{
    /* Construtor parametrizado de pontos com ordem */
    Face::Face(Point first, Point second, Point third) {
        this->setPoints(first, second, third);
    }

    /* Construtor de cópia de face */
    Face::Face(const Face& face) : first(face.first), second(face.second), third(face.third) {}

    /* Definição do primeiro ponto da face */
    void Face::setFirst(Point point) {

        /* Verifica se todos os pontos são compatíveis */
        if (point == this->second || point == this->third)
            std::invalid_argument("incompatible face points");

        /* Associação do ponto */
        this->first = point;
    }

    /* Definição do segundo ponto da face */
    void Face::setSecond(Point point) {

        /* Verifica se todos os pontos são compatíveis */
        if (point == this->first || point == this->third)
            std::invalid_argument("incompatible face points");

        /* Associação do ponto */
        this->second = point;
    }

    /* Definição do terceiro ponto da face */
    void Face::setThird(Point point) {

        /* Verifica se todos os pontos são compatíveis */
        if (point == this->first || point == this->second)
            std::invalid_argument("incompatible face points");

        /* Associação do ponto */
        this->third = point;
    }

    /* Definição de todos os pontos da face */
    void Face::setPoints(Point first, Point second, Point third) {
         
        /* Verifica se todos os pontos são compatíveis */
        if (first == second || second == third || third == first)
            std::invalid_argument("incompatible face points");

        /* Definição dos pontos */
        this->first = first;
        this->second = second;
        this->third = third;
    }

    /* Devolução do primeiro ponto da face */
    const Point& Face::getFirst() const {
        return this->first;
    }

    /* Devolução do segundo ponto da face */
    const Point& Face::getSecond() const {
        return this->second;
    }

    /* Devolução do terceiro ponto da face */
    const Point& Face::getThird() const {
        return this->third;
    }

    /* Definição da normal da face */
    void Face::normal() {

        /* Cálculo da normal da face */
        utils::Matrix normal = this->getNormal();

        /* Aplicação da normal aos respetivos pontos */
        this->first.setNormal(normal);
        this->second.setNormal(normal);
        this->third.setNormal(normal);
    }

    /* Definição das normais da face através de um dicionário */
    void Face::setNormal(std::unordered_map<std::string, Point> normalMap) {

        /* Atualiza os pontos para os presentes no mapa */
        this->first = normalMap[this->first.stringKey()];
        this->second = normalMap[this->second.stringKey()];
        this->third = normalMap[this->third.stringKey()];
    }

    /* Atualização do dicionário de normais através dos pontos das faces */
    void Face::updateNormal(std::unordered_map<std::string, Point> * normalMap) const {

        /* Atualiza o primeiro ponto no mapa */
        if (!(normalMap->emplace(this->first.stringKey(), this->first).second))
            (*normalMap)[this->first.stringKey()].updateNormal(this->first.getNormal());

        /* Atualiza o segundo ponto no mapa */
        if (!(normalMap->emplace(this->second.stringKey(), this->second).second))
            (*normalMap)[this->second.stringKey()].updateNormal(this->second.getNormal());

        /* Atualiza o terceiro ponto no mapa */
        if (!(normalMap->emplace(this->third.stringKey(), this->third).second))
            (*normalMap)[this->third.stringKey()].updateNormal(this->third.getNormal());
    }

    /* Cálculo da normal para uma esfera */
    void Face::sphereNormal() {

        /* Cálculo da normal em todos os pontos */
        this->first.sphereNormal();
        this->second.sphereNormal();
        this->third.sphereNormal();
    }

    /* Cálculo da normal desta face */
    utils::Matrix Face::getNormal() const {

        /* Cálculo da normal */
        utils::Matrix normal = (this->second.getCoords() - this->first.getCoords()).crossVector((this->third.getCoords() - this->first.getCoords())).normalize();

        /* Devolução da normal calculada */
        return normal;
    }

    /* Normalização de todos os pontos de uma face */
    void Face::normalize() {

        /* Aplicação de uma normalização aos três pontos */
        this->first.normalize();
        this->second.normalize();
        this->third.normalize();
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
    void Face::rotate(float angle, float rx, float ry, float rz) {

        /* Criação das matrizes de rotação */
        utils::Matrix rotate = utils::Matrix::rotate(angle, rx, ry, rz);

        /* Aplicação da matriz */
        this->transform(rotate);
    }

    /* Escala de uma face dado um vetor de escala */
    void Face::scale(float sx, float sy, float sz) {

        /* Criação da matriz de escala */
        utils::Matrix scale = utils::Matrix::scale(sx, sy, sz);

        /* Aplicação da matriz */
        this->transform(scale);
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

    /* Operação de clonagem de uma face */
    Face Face::clone() const {
        return Face((*this));
    }

    /* Transformação de uma face em formato string */
    std::string Face::toString() const {

        /* Inicialização da string vazia */
        std::string face = "";

        /* Construção da string que irá representar o ponto */
        face += "1.-" + this->first.toString() + "\n";
        face += "2.-" + this->second.toString() + "\n";
        face += "3.-" + this->third.toString() + "\n";

        /* Devolução da string criada */
        return face;
    }
};
