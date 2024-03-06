#ifndef GEOMETRY_PRIMITIVE_HPP
#define GEOMETRY_PRIMITIVE_HPP

#include "face.hpp"
#include <list>

/* Inicialização do namespace onde a classe irá ser definida */
namespace geometry
{

    /* Definição da classe primitiva */
    class Primitive {
        
        public:

            /* Construtor padrão de primitiva */
            Primitive();

            /* Rotação de todas as faces de uma primitiva para ficarem viradas para o lado oposto */
            virtual void turn() = 0;

            /* Transformação de uma primitiva em formato string */
            virtual std::string toString() const = 0;
    };
}

#endif