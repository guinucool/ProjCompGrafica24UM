/* Inclusão do cabeçalho de definição da estrutura de rotação */
#include "../../../inc/transforms/animated/rotate.hpp"

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>
#include <typeinfo>
#include <cmath>

/* Inicialização do namespace usado para definir a classe de rotação animada */
namespace transforms::animated
{
    /* Construtor padrão vazio de rotação */
    Rotate::Rotate() : Transform(), x(0.0f), y(0.0f), z(0.0f) {}

    /* Construtor parametrizado de rotação */
    Rotate::Rotate(float time, float x, float y, float z) : Transform(time), x(x), y(y), z(z) {}

    /* Construtor de cópia de rotação */
    Rotate::Rotate(const Rotate& rotate) : Transform(rotate), x(rotate.x), y(rotate.y), z(rotate.z) {}

    /* Construtor através de um ficheiro XML de rotação */
    Rotate::Rotate(tinyxml2::XMLElement * transform) : Transform() {
        this->read(transform);
    }

    /* Devolução do valor de rotação aplicada sobre o eixo x, alterável */
    float& Rotate::X() {
        return this->x;
    }

    /* Devolução do valor da rotação aplicada sobre o eixo x */
    const float& Rotate::getX() const {
        return this->x;
    }

    /* Devolução do valor de rotação aplicada sobre o eixo y, alterável */
    float& Rotate::Y() {
        return this->y;
    }

    /* Devolução do valor da rotação aplicada sobre o eixo y */
    const float& Rotate::getY() const {
        return this->y;
    }

    /* Devolução do valor de rotação aplicada sobre o eixo z, alterável */
    float& Rotate::Z() {
        return this->z;
    }

    /* Devolução do valor da rotação aplicada sobre o eixo z */
    const float& Rotate::getZ() const {
        return this->z;
    }

    /* Leitura de uma rotação através de um ficheiro XML */
    void Rotate::read(tinyxml2::XMLElement * transform) {

        /* Verifica se a propriedade de rotação é válida */
        if (transform->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Leitura das propriedades do tempo de rotação */
        Transform::read(transform);

        /* Variáveis que irão armazenar os atributos */
        float x, y, z;

        /* Obtenção dos atributos e verificação da existência deles */
        if (transform->QueryFloatAttribute("x", &x) || transform->QueryFloatAttribute("y", &y) || transform->QueryFloatAttribute("z", &z))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação das propriedades */
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /* Aplicação da rotação ao cenário */
    void Rotate::apply() const {

        /* Cálculo do tempo do estado atual da animação */
        float t = this->getRelativeTime();

        /* Aplicação da rotação animada baseada no tempo atual */
        glRotatef(360 * t, this->x, this->y, this->z);
    }

    /* Define o operador de comparação de igualdade */
    bool Rotate::operator==(const transforms::Transform * transform) const {

        /* Transforma a transformação em rotação */
        Rotate * rotate = (Rotate *) transform;

        /* Verificação de igualdade */
        return ((Transform::operator==(transform)) && (rotate->x == this->x) && (rotate->y == this->y) && (rotate->z == this->z));
    }

    /* Define o operador de comparação de desigualdade */
    bool Rotate::operator!=(const transforms::Transform * transform) const {

        /* Transforma a transformação em rotação */
        Rotate * rotate = (Rotate *) transform;

        /* Verificação de igualdade */
        return ((Transform::operator!=(transform)) || (rotate->x != this->x) || (rotate->y != this->y) || (rotate->z != this->z));
    }

    /* Operação de clonagem de uma rotação */
    transforms::Transform * Rotate::clone() const {
        return new Rotate((*this));
    }

    /* Transformação de uma rotação em formato string */
    std::string Rotate::toString() const {

        /* Criação da string vazia */
        std::string rotate = "";

        /* Preenchimento da string resultado */
        rotate = "(Rotate)" + Transform::toString() + "(" + std::to_string(this->x) + "," + std::to_string(this->y) + "," + std::to_string(this->z) + ")";

        /* Devolução da string construída para resultado */
        return rotate;
    }
}