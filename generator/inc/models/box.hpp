#ifndef BOX_HPP
#define BOX_HPP

#include "../primitives/primitive.hpp"
#include "plane.hpp"

/* Inicialização do namespace usado para definir a classe caixa */
namespace models
{
    
    /* Definição da classe caixa */
    class Box : public primitives::Primitive {

        public:

            /* Construtor padrão parametrizado */
            Box(float length, int divisions);

            /* Construtor de cópia */
            Box(const Box& box);
    };
}

#endif