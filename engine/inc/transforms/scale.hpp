#ifndef SCALE_HPP
#define SCALE_HPP

#include "transform.hpp"

/* Inicialização do namespace usado para definir a classe de escala */
namespace transforms {

    /* Definição da classe de escala */
    class Scale : public Transform {

        public:

            /* Construtor padrão vazio de escala */
            Scale();

            /* Construtor parametrizado de escala */
            Scale(float x, float y, float z);

            /* Construtor de cópia de escala */
            Scale(const Scale& scale);

            /* Construtor através de um ficheiro XML de escala */
            Scale(tinyxml2::XMLElement * transform);

            /* Leitura de uma escala através de um ficheiro XML */
            void read(tinyxml2::XMLElement * transform);

            /* Aplicação da escala ao cenário */
            const void apply() const;

            /* Operação de clonagem de uma escala */
            Transform * clone() const;

            /* Transformação de uma escala em formato string */
            std::string toString() const;

    };
}

#endif