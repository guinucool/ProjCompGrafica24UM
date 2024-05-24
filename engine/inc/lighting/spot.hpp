#ifndef LIGHTSPOT_HPP
#define LIGHTSPOT_HPP

#include "light.hpp"

/* Inicialização do namespace usado para definir a classe luz */
namespace lighting
{
    /* Definição da classe luz */
    class Spot : public Light {

        private:
            
            /* Definição das propriedades da luz */
            float dirX, dirY, dirZ;
            float cutoff;

        protected:

            /* Devolução da referência do valor da coordenada direcional x da luz */
            float& DirX();

            /* Devolução da referência do valor da coordenada direcional y da luz */
            float& DirY();

            /* Devolução da referência do valor da coordenada direcional z da luz */
            float& DirZ();

            /* Atribuição do ângulo de abertura da luz */
            void SetCutoff(float cutoff);

        public:

            /* Construtor de luz vazia (inicializa na origem) */
            Spot();

            /* Construtor de luz parametrizado */
            Spot(float x, float y, float z, float dirX, float dirY, float dirZ, float cutoff);

            /* Construtor de cópia de uma luz */
            Spot(const Spot& spot);

            /* Construtor de uma luz através de um formato XML */
            Spot(tinyxml2::XMLElement * spot);

            /* Devolução do valor da coordenada direcional x da luz  */
            const float& getDirX() const;

            /* Devolução do valor da coordenada direcional y da luz */
            const float& getDirY() const;

            /* Devolução do valor da coordenada direcional z da luz */
            const float& getDirZ() const;

            /* Devolução do valor do ângulo da luz */
            const float& getCutoff() const;

            /* Leitura de uma luz através de um formato XML */
            void read(tinyxml2::XMLElement * spot);

            /* Ativação e desenho de uma luz */
            void enable() const;

            /* Define o operador de comparação de igualdade */
            bool operator==(const Light * light) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const Light * light) const;

            /* Operação de clonagem de uma luz */
            Light * clone() const;

            /* Transformação de uma luz em formato string */
            std::string toString() const;
    };
}

#endif
