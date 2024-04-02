#ifndef ROTATE_HPP
#define ROTATE_HPP

#include "transform.hpp"

/* Inicialização do namespace usado para definir a classe de rotação */
namespace transforms {

    /* Definição da classe de rotação */
    class Rotate : public Transform {

        private:

            /* Definição das propriedades de uma rotação */
            float angle;

        protected:

            /* Devolução do valor do ângulo aplicado sobre a rotação, alterável */
            float& Angle();

        public:

            /* Construtor padrão vazio de rotação */
            Rotate();

            /* Construtor parametrizado de rotação */
            Rotate(float angle, float x, float y, float z);

            /* Construtor de cópia de escala */
            Rotate(const Rotate& rotate);

            /* Construtor através de um ficheiro XML de rotação */
            Rotate(tinyxml2::XMLElement * transform);

            /* Devolução do ângulo da rotação usado */
            const float& getAngle() const;

            /* Leitura de uma rotação através de um ficheiro XML */
            void read(tinyxml2::XMLElement * transform);

            /* Aplicação da rotação ao cenário */
            const void apply() const;

            /* Define o operador de comparação de igualdade */
            bool operator==(const Transform * transform) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const Transform * transform) const;

            /* Operação de clonagem de uma rotação */
            Transform * clone() const;

            /* Transformação de uma rotação em formato string */
            std::string toString() const;

    };
}

#endif