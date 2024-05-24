/* Inclusão do cabeçalho que define a classe esfera */
#include "../../inc/models/sphere.hpp"

/* Inclusão dos módulos necessários para funcionalidade */
#include <stdexcept>
#include <cmath>

/* Inicialização do namespace onde vai ser feita a definição */
namespace models
{
    /* Construtor padrão parametrizado */
    Sphere::Sphere(float radius, int slices, int stacks) {

        /* Verifica a validade das propriedades submetidas */
        if (radius <= 0 || slices < 3 || stacks < 1)
            std::invalid_argument("invalid primitive arguments given");

        /* Cáculo dos ângulos de rotação */
        float alpha = (2 * M_PI) / slices;
        float beta = M_PI / (2 * stacks);

        /* Criação das matrizes de rotação */
        utils::Matrix betaR = utils::Matrix::rotate(beta, 1, 0, 0);
        utils::Matrix alphaR = utils::Matrix::rotate(alpha, 0, 1, 0);

        /* Criação dos pontos de começo */
        primitives::Point start(0, radius, 0);

        /* Criação das pilhas */
        for (int i = 0; i < (stacks * 2); i++)
        {
            /* Criação do novo ponto */
            primitives::Point next = start;

            /* Aplicação da transformação ao novo ponto para o localizar no plano certo da esfera */
            next.transform(betaR);

            /* Criação dos pontos de rotação pelo eixo y */
            primitives::Point startR = start;
            primitives::Point nextR = next;

            /* Rotação dos novos pontos pelo eixo y */
            startR.transform(alphaR);
            nextR.transform(alphaR);

            /* Adição da nova face à esfera */
            if (i == 0)
                this->addTriangle(nextR, start, next);
            else if (i == (stacks * 2) - 1)
                this->addTriangle(startR, start, next);
            else
                this->addSquare(startR, start, next, nextR);

            /* Preparação para a próxima iteração */
            start = next;
        }

        /* Clonagem da fatia atual */
        primitives::Primitive slice = (*this);

        /* Duplicação da fatia atual por várias fatias */
        for (int i = 0; i < (slices - 1); i++) {

            /* Transformação desta fatia na próxima */
            slice.transform(alphaR);

            /* Adição da nova fatia */
            this->add(slice);
        }

        /* Cálculo das normais para a esfera */
        this->sphereNormal();
    }

    /* Construtor de cópia */
    Sphere::Sphere(const Sphere& sphere) : primitives::Primitive(sphere) {}
}