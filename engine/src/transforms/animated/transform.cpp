/* Inclusão do cabeçalho de definição da estrutura de transformação */
#include "../../../inc/transforms/animated/transform.hpp"

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>
#include <typeinfo>

/* Inicialização do namespace utilizado para a definição */
namespace transforms::animated
{
    /* Construtor padrão vazio de transformação */
    Transform::Transform() : time(0.0f) {}

    /* Construtor parametrizado de transformação */
    Transform::Transform(float time) : time(time) {}

    /* Construtor de cópia de transformação */
    Transform::Transform(const Transform& transform) : time(transform.time) {}

    /* Devolução do valor de tempo de execução da transformação, alterável */
    float& Transform::Time() {
        return this->time;
    }

    /* Devolução do valor de tempo de execução da transformação */
    const float& Transform::getTime() const {
        return this->time;
    }

    /* Devolução do valor de tempo relativo da transformação */
    const float& Transform::getRelativeTime() const {
        return glutGet(GLUT_ELAPSED_TIME) / (1000.0f * this->time);
    }

    /* Leitura de uma translação através de um ficheiro XML */
    void Transform::read(tinyxml2::XMLElement * transform) {

        /* Variáveis que irão armazenar os atributos */
        float time;

        /* Obtenção dos atributos e verificação da existência deles */
        if (transform->QueryFloatAttribute("time", &time))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação das propriedades */
        this->time = time;
    }

    /* Define o operador de comparação de igualdade */
    bool Transform::operator==(const transforms::Transform * transform) const {

        /* Transforma a transformação em transformação animada */
        Transform * anim = (Transform *) transform;

        /* Verificação de igualdade */
        return ((typeid(*this) == typeid(*transform)) && (this->time == anim->time));
    }

    /* Define o operador de comparação de desigualdade */
    bool Transform::operator!=(const transforms::Transform * transform) const {

        /* Transforma a transformação em transformação animada */
        Transform * anim = (Transform *) transform;

        /* Verificação de igualdade */
        return ((typeid(*this) != typeid(*transform)) || (this->time != anim->time));
    }

    /* Transformação de uma transformação em formato string */
    std::string Transform::toString() const {

        /* Criação da string vazia */
        std::string transform = "";

        /* Preenchimento da string resultado */
        transform = "(" + std::to_string(this->time) + "s)"; 

        /* Devolução da string construída para resultado */
        return transform;
    }
}