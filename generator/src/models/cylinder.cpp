/* Inclusão do cabeçalho que define a classe esfera */
#include "../../inc/models/cylinder.hpp"

/* Inclusão dos módulos necessários para funcionalidade */
#include <cmath>

/* Inicialização do namespace onde vai ser feita a definição */
namespace models
{
    /* Construtor padrão parametrizado */
    Cylinder::Cylinder(float radius, float height, int slices, int stacks) {
        
        /* Cálculo dos ângulos de rotação e altura de cada stack */
        float alpha = (2 * M_PI) / slices;
        float stackHeight = height / stacks;

        /* Criação das matrizes de rotação */
        utils::Matrix alphaR = utils::Matrix::rotate(alpha, 0, 1, 0);

        /* Criação dos pontos de começo na base */
        primitives::Point bottom(0, -height / 2, 0); // Ponto central inferior
        primitives::Point top(0, height / 2, 0); // Ponto central superior

        /* Loop para criação das stacks */
        for (int i = 0; i <= stacks; i++) {
            float y = -height / 2 + i * stackHeight;

            /* Loop para criação das slices */
            for (int j = 0; j < slices; j++) {

                /* Cálculo dos pontos de cada slice */
                float theta = j * alpha;
                float nextTheta = (j + 1) * alpha;

                primitives::Point p1(radius * cos(theta), y, radius * sin(theta));
                primitives::Point p2(radius * cos(nextTheta), y, radius * sin(nextTheta));
                primitives::Point p3(radius * cos(theta), y + stackHeight, radius * sin(theta));
                primitives::Point p4(radius * cos(nextTheta), y + stackHeight, radius * sin(nextTheta));

                /* Adição da face lateral */
                this->addSquare(p1, p2, p4, p3);
            }
        }

        /* Criação das tampas superior e inferior */
        for (int j = 0; j < slices; j++) {
            float theta = j * alpha;
            float nextTheta = (j + 1) * alpha;

            primitives::Point pBottom1(0, -height / 2, 0);
            primitives::Point pBottom2(radius * cos(theta), -height / 2, radius * sin(theta));
            primitives::Point pBottom3(radius * cos(nextTheta), -height / 2, radius * sin(nextTheta));

            primitives::Point pTop1(0, height / 2, 0);
            primitives::Point pTop2(radius * cos(theta), height / 2, radius * sin(theta));
            primitives::Point pTop3(radius * cos(nextTheta), height / 2, radius * sin(nextTheta));

            /* Adição dos triângulos das tampas */
            this->addTriangle(pBottom1, pBottom3, pBottom2);
            this->addTriangle(pTop1, pTop2, pTop3);
        }
    }

    /* Construtor de cópia */
    Cylinder::Cylinder(const Cylinder& cylinder) : primitives::Primitive(cylinder) {}
}
