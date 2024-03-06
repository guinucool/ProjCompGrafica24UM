#ifndef POINT_HPP
#define POINT_HPP

#include "../../../shared/inc/utils/matrix.hpp"
#include "../../../shared/inc/geometry/point.hpp"
#include <fstream>

/* Inicialização do namespace usado para definir a classe ponto */
namespace primitives
{
    /* Definição da classe ponto */
    class Point : public geometry::Point {

        private:

            /* Definição das propriedades do ponto */
            utils::Matrix coords;

            /* Definição das coordenadas do ponto */
            void setCoords(float x, float y, float z);

        public:

            /* Construtor de ponto vazio (inicializa na origem) */
            Point();

            /* Construtor parametrizado de ponto */
            Point(float x, float y, float z);

            /* Construtor de cópia de ponto */
            Point(const Point& point);

            /* Construtor parametrizado de ponto para coordenadas polares */
            static Point polarPoint(float radius, float theta, float beta);

            /* Devolução da referência do valor da coordenada x do ponto */
            float& X();

            /* Devolução da referência do valor da coordenada x do ponto sem possibilidade de alteração */
            const float& X() const;

            /* Devolução da referência do do valor da coordenada y do ponto */
            float& Y();

            /* Devolução da referência do valor da coordenada y do ponto sem possibilidade de alteração */
            const float& Y() const;

            /* Devolução da referência do do valor da coordenada z do ponto */
            float& Z();

            /* Devolução da referência do valor da coordenada z do ponto sem possibilidade de alteração */
            const float& Z() const;

            /* Devolução da matriz das coordenadas do ponto */
            utils::Matrix getCoords() const;

            /* Transformação de um ponto dada uma matriz */
            void transform(const utils::Matrix& transform);

            /* Translação de um ponto dado um vetor */
            void translateD(float dx, float dy, float dz);

            /* Translação de um ponto dado um vetor polar */
            void translateP(float radius, float theta, float beta);

            /* Rotação de um ponto dado o ângulo de rotação sobre cada eixo */
            void rotate(float ax, float ay, float az);

            /* Escrita de um ponto em ficheiro */
            void write(std::ofstream& stream) const;

            /* Operação de clonagem de um ponto */
            Point clone() const;
    };
}

#endif
