/* Inclusão do cabeçalho que define a classe caixa */
#include "../../inc/models/box.hpp"

/* Inclusão dos módulos necessários para funcionalidade */
#include <cmath>

/* Inicialização do namespace onde vai ser feita a definição */
namespace models
{
    /* Construtor padrão parametrizado */
    Box::Box(float length, int divisions) {

        /* EXCEÇÕES */

        /* Cálculo da coordenada limite */
        float border = length / 2;

        /* Criação de um plano inicial base */
        Plane upDo(length, divisions);

        /* Translação das faces */
        utils::Matrix translate = utils::Matrix::translateD(0, border, 0);

        /* Criação das face oposta da inicial */
        primitives::Primitive down = upDo;

        /* Aplicação das transformações */
        upDo.transform(translate);
        down.transform((utils::Matrix::rotateZ(M_PI)) * translate);

        /* Adição da face oposta */
        upDo.add(down);

        /* Criação dos outros 4 lados */
        primitives::Primitive riLe = upDo;
        primitives::Primitive foBa = upDo;

        /* Rotação dos lados para o local certo */
        riLe.rotate(0, 0, M_PI / 2);
        foBa.rotate(M_PI / 2, 0, 0);
        

        /* Adição das faces à caixa */
        this->add(upDo);
        this->add(riLe);
        this->add(foBa);
    }

    /* Construtor de cópia */
    Box::Box(const Box& box) : primitives::Primitive(box) {}
}