#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP

#include "transform.hpp"

/* Inicialização do namespace usado para definir a classe de translação */
namespace transforms {

    /* Definição da classe de translação */
    class Translate : public Transform {

        public:

            /* Construtor padrão vazio de translação */
            Translate();

            /* Construtor parametrizado de translação */
            Translate(float x, float y, float z);

            /* Construtor de cópia de translação */
            Translate(const Translate& translate);

            /* Construtor através de um ficheiro XML de translação */
            Translate(tinyxml2::XMLElement * transform);

            /* Leitura de uma translação através de um ficheiro XML */
            void read(tinyxml2::XMLElement * transform);

            /* Aplicação da translação ao cenário */
            const void apply() const;

            /* Operação de clonagem de uma translação */
            Transform * clone() const;

            /* Transformação de uma translação em formato string */
            std::string toString() const;

    };
}

#endif