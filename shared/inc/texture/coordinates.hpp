#ifndef TEXTURE_COORDINATES_HPP
#define TEXTURE_COORDINATES_HPP

#include "../utils/matrix.hpp"
#include <fstream>

/* Inicialização do namespace usado para definir a classe de coordenadas */
namespace texture
{
    /* Definição da classe de coordenadas */
    class Coordinates {

        private:

            /* Definição das propriedades de coordenadas de textura */
            float x, y;

        public:

            /* Construtor de coordenadas vazio */
            Coordinates();

            /* Construtor de coordenadas parametrizado */
            Coordinates(float x, float y);
            
            /* Construtor de cópia de coordenadas */
            Coordinates(const Coordinates& coordinates);

            /* Construtor de coordenadas de textura através de um ficheiro */
            Coordinates(std::ifstream& stream);

            /* Devolução da referência do valor da coordenada x do ponto */
            float& X();

            /* Devolução da referência do valor da coordenada x do ponto sem possibilidade de alteração */
            const float& X() const;

            /* Devolução da referência do do valor da coordenada y do ponto */
            float& Y();

            /* Devolução da referência do valor da coordenada y do ponto sem possibilidade de alteração */
            const float& Y() const;

            /* Aplicação das coordenadas para uma superfície plana */
            void surface(float side, utils::Matrix coords);

            /* Aplicação das coordenadas para uma esfera */
            void sphere(utils::Matrix coords);

            /* Aplicação das coordenadas para a lateral de um cone */
            void cone(float height, utils::Matrix coords);

            /* Leitura de coordenadas vindas de um ficheiro */
            void read(std::ifstream& stream);

            /* Escrita de coordenadas em ficheiro */
            void write(std::ofstream& stream) const;

            /* Alimentação de um buffer para desenho em modo VBO */
            void feedBuffer(std::vector<float>& buffer) const;

            /* Operação de comparação por igualdade de coordenadas */
            bool operator==(const Coordinates& coordinates) const;

            /* Operação de comparação por desigualdade de coordenadas */
            bool operator!=(const Coordinates& coordinates) const;

            /* Operação de clonagem das coordenadas */
            Coordinates clone() const;

            /* Transformação das coordenadas em formato string */
            std::string toString() const;
    };
}

#endif