#ifndef STATIC_ROTATE_HPP
#define STATIC_ROTATE_HPP

#include "../../drawables/point.hpp"
#include "transform.hpp"
#include <list>

/* Inicialização do namespace usado para definir a classe de translação animada */
namespace transforms::animated {

    /* Definição da classe de translação */
    class Translate : public Transform {

        private:

            /* Definição das propriedades de uma translação */
            std::list<drawables::Point> points;
            bool align;

        protected:

            /* Adição de um novo ponto à lista de pontos */
            void addPoint(drawables::Point point);

            /* Devolução do valor de alinhamento aplicado sobre a animação, alterável */
            bool& Align();

            /* Aplicação de uma translação com CatmullRom ao cenário */
            void applyCatmullRom(float t) const;

        public:

            /* Construtor padrão vazio de translação */
            Translate();

            /* Construtor parametrizado de translação */
            Translate(float time, bool align, std::list<drawables::Point> points);

            /* Construtor de cópia de translação */
            Translate(const Translate& translate);

            /* Construtor através de um ficheiro XML de translação */
            Translate(tinyxml2::XMLElement * transform);

            /* Devolução do valor da transformação aplicada sobre o eixo y */
            std::list<drawables::Point> getPoints() const;

            /* Devolução do valor de alinhamento aplicado sobre a animação */
            const bool& isAligned() const;

            /* Leitura de uma translação através de um ficheiro XML */
            void read(tinyxml2::XMLElement * transform);

            /* Aplicação da translação ao cenário */
            void apply() const;

            /* Define o operador de comparação de igualdade */
            bool operator==(const transforms::Transform * transform) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const transforms::Transform * transform) const;

            /* Operação de clonagem de uma translação */
            transforms::Transform * clone() const;

            /* Transformação de uma translação em formato string */
            std::string toString() const;

    };
}

#endif