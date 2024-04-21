#ifndef ANIMATED_TRANSLATE_HPP
#define ANIMATED_TRANSLATE_HPP

#include "../../../../shared/inc/utils/matrix.hpp"
#include "../../drawables/point.hpp"
#include "transform.hpp"
#include <vector>

/* Inicialização do namespace usado para definir a classe de translação animada */
namespace transforms::animated {

    /* Definição da classe de translação */
    class Translate : public Transform {

        private:

            /* Definição de propriedades auxiliares ao cálculo da curva */
            static std::vector<utils::Matrix> Y;

            /* Definição das propriedades de uma translação */
            std::vector<drawables::Point> points;
            bool align;
            int index;

            /* Aplicação da translação de Catmull-Rom */
            void catmullRomPath(float t, utils::Matrix M) const;

            /* Aplicação da rotação de Catmull-Rom */
            void catmullRomAlign(float t, utils::Matrix M) const;

            /* Aplicação de uma translação com Catmull-Rom ao cenário */
            void catmullRom(float t) const;

        protected:

            /* Adição de um novo ponto à lista de pontos */
            void addPoint(drawables::Point point);

            /* Devolução do valor de alinhamento aplicado sobre a animação, alterável */
            bool& Align();

            /* Devolução do valor do índice usado para o vetor y desta animação, alterável */
            int& Index();

        public:

            /* Construtor padrão vazio de translação */
            Translate();

            /* Construtor parametrizado de translação */
            Translate(float time, bool align, std::vector<drawables::Point> points);

            /* Construtor de cópia de translação */
            Translate(const Translate& translate);

            /* Construtor através de um ficheiro XML de translação */
            Translate(tinyxml2::XMLElement * transform);

            /* Devolução da lista de pontos que definem a curva */
            std::vector<drawables::Point> getPoints() const;

            /* Devolução do número de pontos que definem a curva*/
            size_t getSize() const;

            /* Devolução do valor do índice usado para o vetor y desta animação */
            const int& getIndex() const;

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