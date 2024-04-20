#ifndef STATIC_ROTATE_HPP
#define STATIC_ROTATE_HPP

#include "transform.hpp"

/* Inicialização do namespace usado para definir a classe de rotação animada */
namespace transforms::animated {

    /* Definição da classe de rotação */
    class Rotate : public Transform {

        private:

            /* Definição das propriedades de uma rotação */
            float x, y, z;

        protected:

            /* Devolução do valor de rotação aplicada sobre o eixo x, alterável */
            float& X();

            /* Devolução do valor de rotação aplicada sobre o eixo y, alterável */
            float& Y();

            /* Devolução do valor de rotação aplicada sobre o eixo z, alterável */
            float& Z();

        public:

            /* Construtor padrão vazio de rotação */
            Rotate();

            /* Construtor parametrizado de rotação */
            Rotate(float time, float x, float y, float z);

            /* Construtor de cópia de rotação */
            Rotate(const Rotate& rotate);

            /* Construtor através de um ficheiro XML de rotação */
            Rotate(tinyxml2::XMLElement * transform);

            /* Devolução do valor da rotação aplicada sobre o eixo x */
            const float& getX() const;

            /* Devolução do valor da rotação aplicada sobre o eixo y */
            const float& getY() const;

            /* Devolução do valor da rotação aplicada sobre o eixo z */
            const float& getZ() const;

            /* Leitura de uma rotação através de um ficheiro XML */
            void read(tinyxml2::XMLElement * transform);

            /* Aplicação da rotação ao cenário */
            void apply() const;

            /* Define o operador de comparação de igualdade */
            bool operator==(const transforms::Transform * transform) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const transforms::Transform * transform) const;

            /* Operação de clonagem de uma rotação */
            transforms::Transform * clone() const;

            /* Transformação de uma rotação em formato string */
            std::string toString() const;

    };
}

#endif