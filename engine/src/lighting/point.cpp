/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/lighting/point.hpp"

/* Inclusão de módulos necessário à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace ao qual a class pertence */
namespace lighting
{
    /* Construtor de luz vazia (inicializa na origem) */
    Point::Point() : Light() {}

    /* Construtor de luz parametrizado */
    Point::Point(float x, float y, float z) : Light(x, y, z) {}

    /* Construtor de cópia de uma luz */
    Point::Point(const Point& point) : Light(point) {}

    /* Construtor de uma luz através de um formato XML */
    Point::Point(tinyxml2::XMLElement * point) : Light() {
        this->read(point);
    }

    /* Leitura de uma luz através de um formato XML */
    void Point::read(tinyxml2::XMLElement * point) {

        /* Verifica se a propriedade de luz é válida */
        if (point->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Variáveis que irão armazenar os atributos */
        float x, y, z;

        /* Obtenção dos atributos e verificação da existência deles */
        if (point->QueryFloatAttribute("posX", &x) || point->QueryFloatAttribute("posY", &y) || point->QueryFloatAttribute("posZ", &z))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação das propriedades */
        this->X() = x;
        this->Y() = y;
        this->Z() = z;
    }

    /* Ativação e desenho de uma luz */
    void Point::enable() const {

        /* Obtenção do índice de luz mais recente */
        GLenum light = fetchIndex();

        /* Criação do array de posição */
        float pos[4] = { this->getX(), this->getY(), this->getZ(), 1.0f };

        /* Ativação da luz */
        glLightfv(light, GL_POSITION, pos);
        glLightf(light, GL_QUADRATIC_ATTENUATION, 1.0f);
        glEnable(light);
    }

    /* Operação de clonagem de uma luz */
    Light * Point::clone() const {
        return new Point((*this));
    }

    /* Transformação de uma luz em formato string */
    std::string Point::toString() const {

        /* Inicialização de uma string */
        std::string light = "(Point-Light)";

        /* Construção da string */
        light += Light::toString();

        /* Devolução da string construída */
        return light;
    }
}