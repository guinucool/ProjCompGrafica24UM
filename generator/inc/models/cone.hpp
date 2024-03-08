#ifndef CONE_HPP
#define CONE_HPP

#include "../primitives/primitive.hpp"

/* Inicialização do namespace ao qual a classe cone pertence */
namespace models
{

    /* Definição da classe cone */
    class Cone : public primitives::Primitive {
        
        public:

            /* Construtor padrão parametrizado */
            Cone(float radius, float height, int slices, int stacks);

            /* Construtor de cópia */
            Cone(const Cone& cone);
    };
}

#endif