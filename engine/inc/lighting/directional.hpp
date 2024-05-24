#ifndef LIGHTDIRECTION_HPP
#define LIGHTDIRECTION_HPP

#include "light.hpp"

/* Inicialização do namespace usado para definir a classe luz */
namespace lighting
{
    /* Definição da classe luz */
    class Directional : public Light {

        public:

            /* Construtor de luz vazia (inicializa na origem) */
            Directional();

            /* Construtor de luz parametrizado */
            Directional(float x, float y, float z);

            /* Construtor de cópia de uma luz */
            Directional(const Directional& directional);

            /* Construtor de uma luz através de um formato XML */
            Directional(tinyxml2::XMLElement * directional);

            /* Leitura de uma luz através de um formato XML */
            void read(tinyxml2::XMLElement * directional);

            /* Ativação e desenho de uma luz */
            void enable() const;

            /* Operação de clonagem de uma luz */
            Light * clone() const;

            /* Transformação de uma luz em formato string */
            std::string toString() const;
    };
}

#endif
