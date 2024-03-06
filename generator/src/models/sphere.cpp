/* Inclusão do cabeçalho que define a classe esfera */
#include "../../inc/models/sphere.hpp"

/* Inclusão dos módulos necessários para funcionalidade */
#include <cmath>

/* Inicialização do namespace onde vai ser feita a definição */
namespace models
{
    /* Construtor padrão parametrizado */
    Sphere::Sphere(float radius, int slices, int stacks) {

        /* Cáculo dos ângulos de rotação */
        float alpha = (2 * M_PI) / slices;
        float beta = M_PI / (2 * stacks);

        /* Criação das matrizes de rotação */
        utils::Matrix betaR = utils::Matrix::rotateX(beta);
        utils::Matrix alphaR = utils::Matrix::rotateY(alpha);

        /* Criação dos pontos de começo */
        primitives::Point start(0, radius, 0);

        /* Criação das pilhas */
        for (int i = 0; i < (stacks * 2); i++)
        {
            /* Criação do novo ponto */
            primitives::Point next = start.clone();

            /* Aplicação da transformação ao novo ponto para o localizar no plano certo da esfera */
            next.transform(betaR);

            /* Criação dos pontos de rotação pelo eixo y */
            primitives::Point startR = start.clone();
            primitives::Point nextR = next.clone();

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
        primitives::Primitive slice = this->clone();

        /* Duplicação da fatia atual por várias fatias */
        for (int i = 0; i < slices; i++) {

            /* Transformação desta fatia na próxima */
            slice.transform(alphaR);

            /* Adição da nova fatia */
            this->add(slice);
        }
    }

    /* Construtor de cópia */
    Sphere::Sphere(const Sphere& sphere) : primitives::Primitive(sphere) {}
}