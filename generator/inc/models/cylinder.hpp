#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "../primitives/primitive.hpp"

/* Inicialização do namespace usado para definir a classe cilindro */
namespace models
{
    
    /* Definição da classe cilindro */
    class Cylinder : public primitives::Primitive {

        public:

            /* Construtor padrão parametrizado */
            Cylinder(float radius, float height, int slices, int stacks);

            /* Construtor de cópia */
            Cylinder(const Cylinder& cylinder);
    };
}

#endif