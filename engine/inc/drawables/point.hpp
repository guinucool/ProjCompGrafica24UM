#ifndef POINT_HPP
#define POINT_HPP

#include "../../../external/tinyxml2/tinyxml2.h"
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

            /* Construtor parametrizado de ponto */
            Point(float x, float y, float z);

            /* Construtor de cópia de ponto */
            Point(const Point& point);

            /* Construtor de ponto através da leitura do ficheiro */
            Point(std::ifstream& stream);

            /* Construtor de ponto através da leitura de uma configuração XML */
            Point(tinyxml2::XMLElement * point);

            /* Construtor parametrizado de ponto para coordenadas polares */
            static Point polarPoint(float radius, float theta, float beta);

            /* Devolução da referência do valor da coordenada x do ponto */
            float& X();

            /* Devolução do valor da coordenada x do ponto  */
            const float& X() const;

            /* Devolução da referência do valor da coordenada y do ponto */
            float& Y();

            /* Devolução do valor da coordenada y do ponto */
            const float& Y() const;

            /* Devolução da referência do valor da coordenada z do ponto */
            float& Z();

            /* Devolução do valor da coordenada z do ponto */
            const float& Z() const;

            /* Negação das coordenadas do ponto */
            void negate();

            /* Leitura de um ponto através de um ficheiro */
            void read(std::ifstream& stream);

            /* Leitura de um ponto através de um formato XML */
            void read(tinyxml2::XMLElement * point);

            /* Desenho de um ponto no modo imediato */
            void draw() const;

            /* Alimentação de um buffer para desenho em modo VBO */
            void feedBuffer(std::vector<float>& buffer) const;

            /* Operação de clonagem de um ponto */
            Point clone() const;
    };
}

#endif
