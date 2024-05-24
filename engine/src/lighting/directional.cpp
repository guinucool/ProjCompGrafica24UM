/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/lighting/directional.hpp"

/* Inclusão de módulos necessário à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace ao qual a class pertence */
namespace lighting
{
    /* Construtor de luz vazia (inicializa na origem) */
    Directional::Directional() : Light() {}

    /* Construtor de luz parametrizado */
    Directional::Directional(float x, float y, float z) : Light(x, y, z) {}

    /* Construtor de cópia de uma luz */
    Directional::Directional(const Directional& directional) : Light(directional) {}

    /* Construtor de uma luz através de um formato XML */
    Directional::Directional(tinyxml2::XMLElement * directional) : Light() {
        this->read(directional);
    }

    /* Leitura de uma luz através de um formato XML */
    void Directional::read(tinyxml2::XMLElement * directional) {

        /* Verifica se a propriedade de luz é válida */
        if (directional->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Variáveis que irão armazenar os atributos */
        float x, y, z;

        /* Obtenção dos atributos e verificação da existência deles */
        if (directional->QueryFloatAttribute("dirX", &x) || directional->QueryFloatAttribute("dirY", &y) || directional->QueryFloatAttribute("dirZ", &z))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação das propriedades */
        this->X() = x;
        this->Y() = y;
        this->Z() = z;
    }

    /* Ativação e desenho de uma luz */
    void Directional::enable() const {

        /* Obtenção do índice de luz mais recente */
        GLenum light = fetchIndex();

        /* Criação do array de posição */
        float pos[4] = { this->getX(), this->getY(), this->getZ(), 0.0f };

        /* Ativação da luz */
        glLightfv(light, GL_POSITION, pos);
        glEnable(light);
    }

    /* Operação de clonagem de uma luz */
    Light * Directional::clone() const {
        return new Directional((*this));
    }

    /* Transformação de uma luz em formato string */
    std::string Directional::toString() const {

        /* Inicialização de uma string */
        std::string light = "(Directional-Light)";

        /* Construção da string */
        light += Light::toString();

        /* Devolução da string construída */
        return light;
    }
}