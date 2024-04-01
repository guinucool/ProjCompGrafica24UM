#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "../../../external/tinyxml2/tinyxml2.h"
#include <string>

/* Inicialização do namespace usado para definir a classe de transformação */
namespace transforms {

    /* Definição da interface de transformação */
    class Transform {

        private:

            /* Definição das propriedades de uma transformação */
            float x, y, z;

        protected:

            /* Devolução do valor de transformação aplicada sobre o eixo x, alterável */
            float& X();

            /* Devolução do valor de transformação aplicada sobre o eixo y, alterável */
            float& Y();

            /* Devolução do valor de transformação aplicada sobre o eixo z, alterável */
            float& Z();

        public:

            /* Construtor padrão vazio de transformação */
            Transform();

            /* Construtor parametrizado de transformação */
            Transform(float x, float y, float z);

            /* Construtor de cópia de transformação */
            Transform(const Transform& transform);

            /* Devolução do valor da transformação aplicada sobre o eixo x */
            const float& getX() const;

            /* Devolução do valor da transformação aplicada sobre o eixo y */
            const float& getY() const;

            /* Devolução do valor da transformação aplicada sobre o eixo z */
            const float& getZ() const;

            /* Leitura de uma transformação através de um ficheiro XML */
            virtual const float& read(tinyxml2::XMLElement * model) const = 0;

            /* Aplicação da transformação ao cenário */
            virtual const void apply() const = 0;

            /* Operação de clonagem de uma transformação*/
            virtual Transform clone() const = 0;

            /* Transformação de uma transformação em formato string */
            std::string toString() const;
    };
}

#endif