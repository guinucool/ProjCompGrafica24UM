/* Inclusão do cabeçalho de definição da estrutura de escala */
#include "../../inc/transforms/scale.hpp"

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

    /* Construtor padrão vazio de escala */
    Scale::Scale() : Transform() {}

    /* Construtor parametrizado de escala */
    Scale::Scale(float x, float y, float z) : Transform(x, y, z) {}

    /* Construtor de cópia de escala */
    Scale::Scale(const Scale& scale) : Transform(scale) {}

    /* Construtor através de um ficheiro XML de escala */
    Scale::Scale(tinyxml2::XMLElement * transform) : Transform() {
        this->read(transform);
    }

    /* Leitura de uma escala através de um ficheiro XML */
    void Scale::read(tinyxml2::XMLElement * transform) {

        /* Verifica se a propriedade de escala é válida */
        if (transform->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Leitura das propriedades da escala */
        Transform::read(transform);
    }

    /* Aplicação da escala ao cenário */
    const void Scale::apply() const {
        glScalef(this->getX(), this->getY(), this->getZ());
    }

    /* Operação de clonagem de uma escala */
    Transform * Scale::clone() const {
        return new Scale((*this));
    }

    /* Transformação de uma escala em formato string */
    std::string Scale::toString() const {

        /* Criação da string vazia */
        std::string scale = "";

        /* Preenchimento da string resultado */
        scale = "(Scale)" + Transform::toString();

        /* Devolução da string construída para resultado */
        return scale;
    }
}