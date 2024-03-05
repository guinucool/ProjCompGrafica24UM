#ifndef PLANE_HPP
#define PLANE_HPP

#include "../primitives/primitive.hpp"

/* Inicialização do namespace ao qual a classe plano pertence */
namespace models
{

    /* Definição da classe plano */
    class Plane : public primitives::Primitive {
        
        public:

            /* Construtor padrão parametrizado */
            Plane(float length, int division);

            /* Construtor de cópia */
            Plane(const Plane& plane);
    };
}

#endif