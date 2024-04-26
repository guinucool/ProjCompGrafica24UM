/* Inclusão do cabeçalho de definição da estrutura de face */
#include "../../inc/drawables/face.hpp"

/* Inclusão de módulos necessários à funcionalidade */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inicialização do namespace ao qual a classe pertence */
namespace drawables
{
    /* Construtor de cópia de face */
    Face::Face(const Face& face) : first(face.first), second(face.second), third(face.third) {}

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

    /* Rotação de uma face para ficar virada para o lado oposto */
    void Face::turn() {

        /* Armazenador auxiliar */
        Point aux = this->first;

        /* Troca de pontos */
        this->first = this->third;
        this->third = aux;
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

        /* Desenho do triângulo que a face representa */
        glBegin(GL_TRIANGLES);
            this->first.draw();
            this->second.draw();
            this->third.draw();
        glEnd();
    }

    /* Alimentação de um buffer para desenho em modo VBO */
    void Face::feedBuffer(std::vector<float>& buffer) const {
        this->first.feedBuffer(buffer);
        this->second.feedBuffer(buffer);
        this->third.feedBuffer(buffer);
    }

    /* Operação de clonagem de uma face */
    Face Face::clone() const {
        return Face((*this));
    }
};