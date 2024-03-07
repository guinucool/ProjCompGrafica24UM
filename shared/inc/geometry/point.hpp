#ifndef GEOMETRY_POINT_HPP
#define GEOMETRY_POINT_HPP

#include <string>

/* Inicialização do namespace usado para definir a classe ponto */
namespace geometry
{
    /* Definição da classe abstrata ponto */
    class Point {

        public:

            /* Construtor vazio */
            Point();

            /* Devolução da referência do valor da coordenada x do ponto */
            virtual float& X() = 0;

            /* Devolução do valor da coordenada x do ponto */
            virtual const float& X() const = 0;

            /* Devolução da referência do valor da coordenada y do ponto */
            virtual float& Y() = 0;

            /* Devolução do valor da coordenada y do ponto */
            virtual const float& Y() const = 0;

            /* Devolução da referência do valor da coordenada z do ponto */
            virtual float& Z() = 0;

            /* Devolução do valor da coordenada z do ponto */
            virtual const float& Z() const = 0;

            /* Operação de comparação por igualdade de pontos */
            bool operator==(const Point& point) const;

            /* Operação de comparação por desigualdade de pontos */
            bool operator!=(const Point& point) const;

            /* Transformação de um ponto em formato string */
            std::string toString() const;
    };
}

#endif
