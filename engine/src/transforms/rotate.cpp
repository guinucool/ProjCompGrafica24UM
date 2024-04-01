/* Inclusão do cabeçalho de definição da estrutura de rotação */
#include "../../inc/transforms/rotate.hpp"

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace utilizado para a definição */
namespace transforms {

    /* Construtor padrão vazio de rotação */
    Rotate::Rotate() : Transform() {}

    /* Construtor parametrizado de rotação */
    Rotate::Rotate(float angle, float x, float y, float z) : Transform(x, y, z), angle(angle) {}

    /* Construtor de cópia de rotação */
    Rotate::Rotate(const Rotate& rotate) : Transform(rotate), angle(rotate.angle) {}

    /* Construtor através de um ficheiro XML de rotação */
    Rotate::Rotate(tinyxml2::XMLElement * transform) : Transform() {
        this->read(transform);
    }

    /* Devolução do valor do ângulo aplicado sobre a rotação, alterável */
    float& Rotate::Angle() {
        return this->angle;
    }

    /* Devolução do ângulo da rotação usado */
    const float& Rotate::getAngle() const {
        return this->angle;
    }

    /* Leitura de uma rotação através de um ficheiro XML */
    void Rotate::read(tinyxml2::XMLElement * transform) {

        /* Verifica se a propriedade de translação é válida */
        if (transform->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Leitura das propriedades do eixo da rotação */
        Transform::read(transform);

        /* Variável que irá armazenar o ângulo lido */
        float angle;

        /* Leitura e verificação do ângulo de rotação */
        if (transform->QueryFloatAttribute("angle", &angle))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação de propriedades */
        this->angle = angle;
    }

    /* Aplicação da rotação ao cenário */
    const void Rotate::apply() const {
        glRotatef(this->angle, this->getX(), this->getY(), this->getZ());
    }

    /* Operação de clonagem de uma rotação */
    Transform * Rotate::clone() const {
        return new Rotate((*this));
    }

    /* Transformação de uma rotação em formato string */
    std::string Rotate::toString() const {

        /* Criação da string vazia */
        std::string rotate = "";

        /* Preenchimento da string resultado */
        rotate = "(Rotate)(" + std::to_string(this->angle) + ")" + Transform::toString();

        /* Devolução da string construída para resultado */
        return rotate;
    }
}