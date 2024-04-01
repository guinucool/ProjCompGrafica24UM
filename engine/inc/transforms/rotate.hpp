#ifndef SCALE_HPP
#define SCALE_HPP

#include "transform.hpp"

/* Inicialização do namespace usado para definir a classe de rotação */
namespace transforms {

    /* Definição da classe de rotação */
    class Rotate : public Transform {

        public:

            /* Construtor padrão vazio de rotação */
            Rotate();

            /* Construtor parametrizado de rotação */
            Rotate(float x, float y, float z);

            /* Construtor de cópia de escala */
            Rotate(const Rotate& rotate);

            /* Construtor através de um ficheiro XML de rotação */
            Rotate(tinyxml2::XMLElement * model);

            /* Devolução do ângulo da rotação usado */
            const float& getAngle() const;

            /* Leitura de uma rotação através de um ficheiro XML */
            const float& read(tinyxml2::XMLElement * model);

            /* Aplicação da rotação ao cenário */
            const void apply() const;

            /* Operação de clonagem de uma rotação */
            Transform clone() const;

            /* Transformação de uma rotação em formato string */
            std::string toString() const;

    };
}

#endif