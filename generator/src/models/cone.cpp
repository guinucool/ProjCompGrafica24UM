/* Inclusão do cabeçalho da classe plano */
#include "../../inc/models/cone.hpp"

/* Inclusão de módulos essenciais à funcionalidade */
#include <cmath>

/* Inicialização do namespace utilizado para a definição da classe */
namespace models
{
    /* Construtor parametrizado da classe plano */
    Cone::Cone(float radius, float height, int slices, int stacks) {

        /* EXCEÇÕES */

        /* Cálculo do ângulo de cada fatia do cone */
        float angle = (2 * M_PI) / slices;

        /* Cálculo do ângulo complementar da abertura do cone */
        float opening = (M_PI / 2) - tanh(radius / height);

        /* Cálculo de uma parte da hipótenusa do cone */
        float hip = sqrt((height * height) + (radius * radius)) / stacks;

        /* Cálculo do ângulo no plano xz da abertura do cone */
        float baseopen = angle - M_PI;

        /* Criação das translações */
        utils::Matrix translateOrigin = utils::Matrix::translateP(hip, M_PI, opening);
        utils::Matrix translateSide = utils::Matrix::translateP(hip, baseopen, opening);

        /* Criação dos pontos da base do cone */
        primitives::Point origin(0, 0, radius);
        primitives::Point side = primitives::Point::polarPoint(radius, angle, 0);

        /* Criação da base do cone */
        this->addTriangle(origin, primitives::Point(), side);

        /* Criação da primeira fatia do cone */
        for (int i = 0; i < stacks; i++) {

            /* Criação dos pontos para completar a face */
            primitives::Point originNext = origin;
            primitives::Point sideNext = side;

            /* Translações dos pontos para a sua posição correta */
            originNext.transform(translateOrigin);
            sideNext.transform(translateSide);

            /* Criação da face lateral */
            if (i == (stacks - 1))
                this->addTriangle(side, originNext, origin);
            else
                this->addSquare(sideNext, originNext, origin, side);

            /* Preparação para a próxima iteração */
            origin = originNext;
            side = sideNext;
        }

        /* Separação da fatia da figura */
        primitives::Primitive slice = (*this);

        /* Criação da rotação */
        utils::Matrix rotation = utils::Matrix::rotateY(angle);

        /* Multiplicação da fatia para completar a figura */
        for (int i = 0; i < (slices - 1); i++) {

            /* Transformação da fatia para a próxima fatia */
            slice.transform(rotation);

            /* Adição da nova fatia rodada à figura final */
            this->add(slice);
        }
    }

    /* Construtor de cópia da classe plano */
    Cone::Cone(const Cone& cone) : primitives::Primitive(cone) {}
}