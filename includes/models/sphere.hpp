#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../primitives/primitive.hpp"

/* Inicialização do namespace usado para definir a classe esfera */
namespace models
{
    
    /* Definição da classe esfera */
    class Sphere : public primitives::Primitive {

        public:

            /* Construtor padrão parametrizado */
            Sphere(float radius, int slices, int stacks);

            /* Construtor de cópia */
            Sphere(const Sphere& sphere);
    };
}

#endif