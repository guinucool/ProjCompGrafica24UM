/* Inclusão do cabeçalho da classe plano */
#include "../../inc/models/cone.hpp"

/* Inclusão de módulos essenciais à funcionalidade */
#include <stdexcept>
#include <cmath>

/* Inicialização do namespace utilizado para a definição da classe */
namespace models
{
    /* Construtor parametrizado da classe plano */
    Cone::Cone(float radius, float height, int slices, int stacks) {

        /* Verifica a validade das propriedades submetidas */
        if (radius <= 0 || height <= 0 || slices < 3 || stacks < 1)
            std::invalid_argument("invalid primitive arguments given");

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

        /* Criação de uma primitiva para a base do cone */
        primitives::Primitive base;

        /* Criação da base do cone */
        base.addTriangle(origin, primitives::Point(), side);

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
                this->addTriangle(side, primitives::Point(0, height, 0), origin);
            else
                this->addSquare(sideNext, originNext, origin, side);

            /* Preparação para a próxima iteração */
            origin = originNext;
            side = sideNext;
        }

        /* Separação da fatia da figura */
        primitives::Primitive slice = (*this);
        primitives::Primitive baseSlice = base;

        /* Cálculo das coordenadas de textura para a lateral */
        this->coneCoordinates(height, false);

        /* Criação da rotação */
        utils::Matrix rotation = utils::Matrix::rotate(angle, 0, 1, 0);

        /* Multiplicação da fatia para completar a figura */
        for (int i = 0; i < (slices - 1); i++) {

            /* Transformação da fatia para a próxima fatia */
            slice.transform(rotation);
            baseSlice.transform(rotation);

            /* Cálculo das coordenadas de textura para a lateral */
            slice.coneCoordinates(height, i == (slices - 2));

            /* Adição da nova fatia rodada à figura final */
            base.add(baseSlice);
            this->add(slice);
        }

        /* Cálculo das normais para o cone */
        base.interpolationNormal();
        this->interpolationNormal();

        /* Cálculo das coordenadas de textura para a base */
        base.surfaceCoordinates(radius * 2);

        /* Junção da base e da lateral */
        this->add(base);
    }

    /* Construtor de cópia da classe plano */
    Cone::Cone(const Cone& cone) : primitives::Primitive(cone) {}
}