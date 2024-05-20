#ifndef LIGHTPOINT_HPP
#define LIGHTPOINT_HPP

#include "light.hpp"

/* Inicialização do namespace usado para definir a classe luz */
namespace lighting
{
    /* Definição da classe luz */
    class Point : public Light {

        public:

            /* Construtor de luz vazia (inicializa na origem) */
            Point();

            /* Construtor de luz parametrizado */
            Point(float x, float y, float z);

            /* Construtor de cópia de uma luz */
            Point(const Point& point);

            /* Construtor de uma luz através de um formato XML */
            Point(tinyxml2::XMLElement * point);

            /* Leitura de uma luz através de um formato XML */
            void read(tinyxml2::XMLElement * point);

            /* Ativação e desenho de uma luz */
            void enable();

            /* Operação de clonagem de uma luz */
            Light * clone() const;

            /* Transformação de uma luz em formato string */
            std::string toString() const;
    };
}

#endif
