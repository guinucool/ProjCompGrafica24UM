#ifndef POINT_HPP
#define POINT_HPP

#include "../../../shared/inc/geometry/point.hpp"
#include <fstream>
#include <vector>

/* Inicialização do namespace usado para definir a classe ponto */
namespace drawables
{
    /* Definição da classe ponto */
    class Point : public geometry::Point {

        private:

            /* Definição das propriedades do ponto */
            float x, y, z;

        public:

            /* Construtor de ponto vazio (inicializa na origem) */
            Point();

            /* Construtor de cópia de ponto */
            Point(const Point& point);

            /* Construtor de ponto através da leitura do ficheiro */
            Point(std::ifstream& stream);

            /* Devolução do valor da coordenada x do ponto */
            const float& X() const;

            /* Devolução do valor da coordenada y do ponto */
            const float& Y() const;

            /* Devolução do valor da coordenada z do ponto */
            const float& Z() const;

            /* Leitura de um ponto através de um ficheiro */
            void read(std::ifstream& stream);

            /* Desenho de um ponto no modo imediato */
            void draw() const;

            /* Alimentação de um buffer para desenho em modo VBO */
            void feedBuffer(std::vector<float>& buffer) const;

            /* Operação de clonagem de um ponto */
            Point clone() const;
    };
}

#endif
