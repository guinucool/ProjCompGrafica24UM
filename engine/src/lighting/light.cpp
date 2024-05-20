/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/lighting/light.hpp"

/* Inclusão de bibliotecas necessárias à funcionalidade */
#include <stdexcept>
#include <typeinfo>

/* Inicialização do namespace ao qual a class pertence */
namespace lighting
{
    /* Inicialização do contador de luzes global */
    GLenum Light::light = GL_LIGHT0;

    /* Devolução da referência do valor da coordenada x da luz */
    float& Light::X() {
        return this->x;
    }

    /* Devolução da referência do valor da coordenada y da luz */
    float& Light::Y() {
        return this->y;
    }

    /* Devolução da referência do valor da coordenada z da luz */
    float& Light::Z() {
        return this->z;
    }

    /* Atribuição de um índice à luz */
    GLenum Light::fetchIndex() {

        /* Verifica se existe espaço para esta luz no cenário */
        if (Light::light > GL_LIGHT7)
            throw std::out_of_range("light limit reached");

        /* Atribuição do índice da luz */
        return Light::light++;
    }

    /* Construtor de luz vazia (inicializa na origem) */
    Light::Light() : x(0), y(0), z(0) {}

    /* Construtor de luz parametrizado */
    Light::Light(float x, float y, float z) : x(x), y(y), z(z) {}

    /* Construtor de cópia de uma luz */
    Light::Light(const Light& light) : x(light.x), y(light.y), z(light.z) {}

    /* Devolução do valor da coordenada x da luz  */
    const float& Light::getX() const {
        return this->x;
    }

    /* Devolução do valor da coordenada y da luz */
    const float& Light::getY() const {
        return this->y;
    }

    /* Devolução do valor da coordenada z da luz */
    const float& Light::getZ() const {
        return this->z;
    }

    /* Desativação de uma luz */
    void Light::disable() {
        
        /* Verifica se existem luzes por desativar */
        if (Light::light == GL_LIGHT0)
            throw std::out_of_range("all lights are disabled");

        /* Desativa a luz mais recente */
        glDisable(Light::light--);
    }

    /* Define o operador de comparação de igualdade */
    bool Light::operator==(const Light * light) const {
        return ((typeid(*this) == typeid(*light)) && (this->x == light->x) && (this->y == light->y) && (this->z == light->z));
    }

    /* Define o operador de comparação de desigualdade */
    bool Light::operator!=(const Light * light) const {
        return ((typeid(*this) != typeid(*light)) || (this->x != light->x) || (this->y != light->y) || (this->z != light->z));
    }

    /* Transformação de uma luz em formato string */
    std::string Light::toString() const {

        /* Inicialização de uma string vazia */
        std::string light = "";

        /* Construção da string */
        light += "(" + std::to_string(this->x) + "," + std::to_string(this->y) + "," + std::to_string(this->z) + ")";

        /* Devolução da string construída */
        return light;
    }
}
