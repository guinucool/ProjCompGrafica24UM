/* Inclusão do cabeçalho de definição da estrutura de transformação */
#include "../../inc/transforms/transform.hpp"

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>
#include <typeinfo>

/* Inicialização do namespace utilizado para a definição */
namespace transforms
{
    /* Construtor padrão vazio de transformação */
    Transform::Transform() : x(0.0f), y(0.0f), z(0.0f) {}

    /* Construtor parametrizado de transformação */
    Transform::Transform(float x, float y, float z) : x(x), y(y), z(z) {}

    /* Construtor de cópia de transformação */
    Transform::Transform(const Transform& transform) : x(transform.x), y(transform.y), z(transform.z) {}

    /* Devolução do valor de transformação aplicada sobre o eixo x, alterável */
    float& Transform::X() {
        return this->x;
    }

    /* Devolução do valor da transformação aplicada sobre o eixo x */
    const float& Transform::getX() const {
        return this->x;
    }

    /* Devolução do valor de transformação aplicada sobre o eixo y, alterável */
    float& Transform::Y() {
        return this->y;
    }

    /* Devolução do valor da transformação aplicada sobre o eixo y */
    const float& Transform::getY() const {
        return this->y;
    }

    /* Devolução do valor de transformação aplicada sobre o eixo z, alterável */
    float& Transform::Z() {
        return this->z;
    }

    /* Devolução do valor da transformação aplicada sobre o eixo z */
    const float& Transform::getZ() const {
        return this->z;
    }

    /* Leitura de uma translação através de um ficheiro XML */
    void Transform::read(tinyxml2::XMLElement * transform) {

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

    /* Define o operador de comparação de igualdade */
    bool Transform::operator==(const Transform * transform) const {
        return ((typeid(*this) == typeid(*transform)) && (this->x == transform->x) && (this->y == transform->y) && (this->z == transform->z));
    }

    /* Define o operador de comparação de desigualdade */
    bool Transform::operator!=(const Transform * transform) const {
        return ((typeid(*this) != typeid(*transform)) || (this->x != transform->x) || (this->y != transform->y) || (this->z != transform->z));
    }

    /* Transformação de uma transformação em formato string */
    std::string Transform::toString() const {

        /* Criação da string vazia */
        std::string transform = "";

        /* Preenchimento da string resultado */
        transform = "(" + std::to_string(this->x) + "," + std::to_string(this->y) + "," + std::to_string(this->z) + ")"; 

        /* Devolução da string construída para resultado */
        return transform;
    }
}