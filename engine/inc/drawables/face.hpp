#ifndef FACE_HPP
#define FACE_HPP

#include "../../../shared/inc/geometry/face.hpp"
#include "point.hpp"

/* Inicialização do namespace usado para definir a classe face */
namespace drawables
{

    /* Definição da classe face */
    class Face : public geometry::Face {
        
        private:

            /* Definição das propriedades da face */
            Point first, second, third;

        public:

            /* Construtor de cópia de uma face */
            Face(const Face& face);

            /* Construtor de face através de um ficheiro */
            Face(std::ifstream& stream);

            /* Devolução do primeiro ponto da face */
            const Point& getFirst() const;

            /* Devolução do segundo ponto da face */
            const Point& getSecond() const;

            /* Devolução do terceiro ponto da face */
            const Point& getThird() const;

            /* Rotação de uma face para ficar virada para o lado oposto */
            void turn();

            /* Leitura de um ponto através de um ficheiro */
            void read(std::ifstream& stream);

            /* Desenho de um ponto no modo imediato */
            void draw() const;

            /* Alimentação de um buffer para desenho em modo VBO */
            void feedBuffer(std::vector<float>& buffer) const;

            /* Operação de clonagem de uma face */
            Face clone() const;
    };
}
#endif
