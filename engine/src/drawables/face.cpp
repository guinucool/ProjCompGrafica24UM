/* Inclusão do cabeçalho de definição da estrutura de face */
#include "../../inc/drawables/face.hpp"

/* Inclusão de módulos necessários à funcionalidade */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

/* Inicialização do namespace ao qual a classe pertence */
namespace drawables
{
    /* Construtor de cópia de face */
    Face::Face(const Face& face) : first(face.first), second(face.second), third(face.third), fNormal(face.fNormal), sNormal(face.sNormal), tNormal(face.tNormal) {}

    /* Construtor de face através de um ficheiro */
    Face::Face(std::ifstream& stream) {
        this->read(stream);
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

    /* Devolução da primeira normal da face */
    const Point& Face::getFirstNormal() const {
        return this->fNormal;
    }

    /* Devolução da segunda normal da face */
    const Point& Face::getSecondNormal() const {
        return this->sNormal;
    }

    /* Devolução da terceira normal da face */
    const Point& Face::getThirdNormal() const {
        return this->tNormal;
    }

    /* Rotação de uma face para ficar virada para o lado oposto */
    void Face::turn() {

        /* Armazenador auxiliar */
        Point aux = this->first;

        /* Troca de pontos */
        this->first = this->third;
        this->third = aux;

        /* Negação das normais */
        this->fNormal.negate();
        this->sNormal.negate();
        this->tNormal.negate();
    }

    /* Leitura de uma face através de um ficheiro */
    void Face::read(std::ifstream &stream) {
        
        /* Leitura do valor dos três pontos vindos de um ficheiro */
        this->first.read(stream);
        this->fNormal.read(stream);
        this->second.read(stream);
        this->sNormal.read(stream);
        this->third.read(stream);
        this->tNormal.read(stream);
    }

    /* Desenho de uma face no modo imediato */
    void Face::draw() const {

        /* Desenho do triângulo que a face representa */
        glBegin(GL_TRIANGLES);
            this->first.draw();
            this->second.draw();
            this->third.draw();
        glEnd();
    }

    /* Alimentação de um buffer para pontos para desenho em modo VBO */
    void Face::feedBufferPoints(std::vector<float>& buffer) const {
        this->first.feedBuffer(buffer);
        this->second.feedBuffer(buffer);
        this->third.feedBuffer(buffer);
    }

    /* Alimentação de um buffer para normais para desenho em modo VBO */
    void Face::feedBufferNormals(std::vector<float>& buffer) const {
        this->fNormal.feedBuffer(buffer);
        this->sNormal.feedBuffer(buffer);
        this->tNormal.feedBuffer(buffer);
    }

    /* Define o operador de comparação de igualdade */
    bool Face::operator==(const Face& face) const {
        return geometry::Face::operator==(face) && this->fNormal == face.fNormal && this->sNormal == face.sNormal && this->tNormal == face.tNormal;
    }

    /* Define o operador de comparação de desigualdade */
    bool Face::operator!=(const Face& face) const {
        return geometry::Face::operator!=(face) || this->fNormal != face.fNormal || this->sNormal != face.sNormal || this->tNormal != face.tNormal;
    }

    /* Operação de clonagem de uma face */
    Face Face::clone() const {
        return Face((*this));
    }

    /* Converte o grupo num formato string */
    std::string Face::toString() const {

        /* Criação da string resultado */
        std::string face = geometry::Face::toString();

        /* Construção da string */
        face += this->fNormal.toString() + '\n';
        face += this->sNormal.toString() + '\n';
        face += this->tNormal.toString() + '\n';

        /* Devolução da string construída */
        return face;
    }
};