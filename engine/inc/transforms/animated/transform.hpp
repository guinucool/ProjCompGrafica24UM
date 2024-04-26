#ifndef ANIMATED_TRANSFORM_HPP
#define ANIMATED_TRANSFORM_HPP

#include "../transform.hpp"

/* Inicialização do namespace usado para definir a classe de transformação animada */
namespace transforms::animated {

    /* Definição da interface de transformação */
    class Transform : public transforms::Transform {

        private:

            /* Definição das propriedades de uma transformação */
            float time;

        protected:

            /* Devolução do valor de tempo de execução da transformação, alterável */
            float& Time();

        public:

            /* Construtor padrão vazio de transformação */
            Transform();

            /* Construtor parametrizado de transformação */
            Transform(float time);

            /* Construtor de cópia de transformação */
            Transform(const Transform& transform);

            /* Devolução do valor de tempo de execução da transformação */
            const float& getTime() const;

            /* Devolução do valor de tempo relativo da transformação */
            float getRelativeTime() const;

            /* Devolução do valor de tempo global */
            float getGlobalTime() const;

            /* Leitura de uma transformação através de um ficheiro XML */
            void read(tinyxml2::XMLElement * transform);

            /* Aplicação da transformação ao cenário */
            virtual void apply() const = 0;

            /* Define o operador de comparação de igualdade */
            bool operator==(const transforms::Transform * transform) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const transforms::Transform * transform) const;

            /* Operação de clonagem de uma transformação*/
            virtual transforms::Transform * clone() const = 0;

            /* Transformação de uma transformação em formato string */
            std::string toString() const;
    };
}

#endif