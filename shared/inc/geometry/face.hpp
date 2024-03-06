#ifndef GEOMETRY_FACE_HPP
#define GEOMETRY_FACE_HPP

#include "point.hpp"
#include <fstream>
#include <string>
#include <list>

/* Inicialização do namespace usado para definir a classe abstrata face */
namespace geometry
{

    /* Definição da classe face */
    class Face {

        protected:

            /* Redefinir os pontos da face */
            virtual void reset(Point first, Point second, Point third) = 0;

        public:

            /* Construtor vazio padrão */
            Face();

            /* Devolução do primeiro ponto da face */
            virtual Point getFirst() const = 0;

            /* Devolução do segundo ponto da face */
            virtual Point getSecond() const = 0;

            /* Devolução do terceiro ponto da face */
            virtual Point getThird() const = 0;

            /* Rotação de uma face para ficar virada para o lado oposto */
            void turn();
            
            /* Operação de comparação por igualdade de faces */
            bool operator==(const Face& face) const;

            /* Operação de comparação por desigualdade de faces */
            bool operator!=(const Face& face) const;

            /* Transformação de uma face em formato string */
            std::string toString() const;
    };
}
#endif
