#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "../../../external/tinyxml2/tinyxml2.h"
#include <string>

/* Inicialização do namespace usado para definir a classe de transformação */
namespace transforms {

    /* Definição da interface de transformação */
    class Transform {

        public:

            /* Construtor padrão vazio de transformação */
            Transform();

            /* Leitura de uma transformação através de um ficheiro XML */
            virtual void read(tinyxml2::XMLElement * transform) = 0;

            /* Aplicação da transformação ao cenário */
            virtual void apply() const = 0;

            /* Define o operador de comparação de igualdade */
            virtual bool operator==(const Transform * transform) const = 0;

            /* Define o operador de comparação de desigualdade */
            virtual bool operator!=(const Transform * transform) const = 0;

            /* Operação de clonagem de uma transformação*/
            virtual Transform * clone() const = 0;

            /* Transformação de uma transformação em formato string */
            virtual std::string toString() const = 0;
    };
}

#endif