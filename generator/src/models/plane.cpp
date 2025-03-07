/* Inclusão do cabeçalho da classe plano */
#include "../../inc/models/plane.hpp"

/* Inclusão dos módulos necessários para funcionalidade */
#include <stdexcept>

/* Inicialização do namespace utilizado para a definição da classe */
namespace models
{
    /* Construtor parametrizado da classe plano */
    Plane::Plane(float length, int divisions) {

        /* Verifica a validade das propriedades submetidas */
        if (length <= 0 || divisions < 1)
            std::invalid_argument("invalid primitive arguments given");

        /* Calculo do comprimento de cada partição */
        float dvlen = length / divisions;

        /* Calculo da coordenada limite */
        float border = length / 2;

        /* Inicialização do primeiro quadrado */
        primitives::Primitive square;
        square.addSquare(primitives::Point(-border + dvlen, 0, -border),
                         primitives::Point(-border, 0, -border),
                         primitives::Point(-border, 0, -border + dvlen),
                         primitives::Point(-border + dvlen, 0, -border + dvlen));

        /* Adição do quadrado à estrutura */
        this->add(square);

        /* Translação no eixo z */
        utils::Matrix tz = utils::Matrix::translateD(0, 0, dvlen);

        /* Translação no eixo x */
        utils::Matrix tx = utils::Matrix::translateD(dvlen, 0, 0);

        /* Crição da primeira coluna de quadrados */
        for (int i = 0; i < (divisions - 1); i++) {

            /* Translação do quadrado */
            square.transform(tz);

            /* Adição do quadrado à figura */
            this->add(square);
        }
        
        /* Clonagem da primeira coluna */
        primitives::Primitive col = (*this);

        /* Multiplicação da primeira coluna pelas restantes */
        for (int i = 0; i < (divisions - 1); i++) {

            /* Translação do quadrado */
            col.transform(tx);

            /* Adição do quadrado à figura */
            this->add(col);
        }

        /* Cálculo das normais para o plano */
        this->interpolationNormal();

        /* Cálculo das coordenadas de textura */
        this->surfaceCoordinates(length);
    }

    /* Construtor de cópia da classe plano */
    Plane::Plane(const Plane& plane) : primitives::Primitive(plane) {}
}