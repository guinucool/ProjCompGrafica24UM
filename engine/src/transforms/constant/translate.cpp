/* Inclusão do cabeçalho de definição da estrutura de translação */
#include "../../../inc/transforms/constant/translate.hpp"

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace utilizado para a definição */
namespace transforms::constant
{
    /* Construtor padrão vazio de translação */
    Translate::Translate() : Transform() {}

    /* Construtor parametrizado de translação */
    Translate::Translate(float x, float y, float z) : Transform(x, y, z) {}

    /* Construtor de cópia de translação */
    Translate::Translate(const Translate& translate) : Transform(translate) {}

    /* Construtor através de um ficheiro XML de translação */
    Translate::Translate(tinyxml2::XMLElement * transform) : Transform() {
        this->read(transform);
    }

    /* Leitura de uma translação através de um ficheiro XML */
    void Translate::read(tinyxml2::XMLElement * transform) {

        /* Verifica se a propriedade de translação é válida */
        if (transform->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Leitura das propriedades da translação */
        Transform::read(transform);
    }

    /* Aplicação da translação ao cenário */
    void Translate::apply() const {
        glTranslatef(this->getX(), this->getY(), this->getZ());
    }

    /* Operação de clonagem de uma translação */
    transforms::Transform * Translate::clone() const {
        return new Translate((*this));
    }

    /* Transformação de uma translação em formato string */
    std::string Translate::toString() const {

        /* Criação da string vazia */
        std::string translate = "";

        /* Preenchimento da string resultado */
        translate = "(Translate)" + Transform::toString();

        /* Devolução da string construída para resultado */
        return translate;
    }
}