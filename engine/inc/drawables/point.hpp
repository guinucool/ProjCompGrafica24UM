#ifndef POINT_HPP
#define POINT_HPP

#include "../../../shared/inc/utils/matrix.hpp"
#include <fstream>
#include <string>

/* Inicialização do namespace usado para definir a classe ponto */
namespace drawables
{
    /* Definição da classe ponto */
    class Point {

        private:

            /* Definição das propriedades do ponto */
            float x, y, z;

        public:

            /* Construtor de ponto vazio (inicializa na origem) */
            Point();

            /* Construtor de ponto através da leitura do ficheiro */
            Point(std::ifstream& stream);

            /* Devolução do valor da coordenada x do ponto */
            float X();

            /* Devolução do valor da coordenada y do ponto */
            float Y();

            /* Devolução do valor da coordenada z do ponto */
            float Z();

            /* Leitura de um ponto através de um ficheiro */
            void read(std::ifstream& stream);

            /* Desenho de um ponto no modo imediato */
            void draw() const;

            /* Alimentação de um buffer para desenho em modo VBO */
            void feedBuffer(std::vector<float>& buffer) const;

            /* Operação de comparação por igualdade de pontos */
            bool operator==(const Point& point) const;

            /* Operação de comparação por desigualdade de pontos */
            bool operator!=(const Point& point) const;

            /* Transformação de um ponto em formato string */
            std::string toString() const;
    };
}

#endif
