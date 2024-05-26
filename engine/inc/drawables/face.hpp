#ifndef FACE_HPP
#define FACE_HPP

#include "../../../shared/inc/geometry/face.hpp"
#include "../../../shared/inc/texture/coordinates.hpp"
#include "point.hpp"

/* Inicialização do namespace usado para definir a classe face */
namespace drawables
{

    /* Definição da classe face */
    class Face : public geometry::Face {
        
        private:

            /* Definição das propriedades da face */
            Point first, second, third;
            Point fNormal, sNormal, tNormal;
            texture::Coordinates ft, st, tt;

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

            /* Devolução da primeira normal da face */
            const Point& getFirstNormal() const;

            /* Devolução da segunda normal da face */
            const Point& getSecondNormal() const;

            /* Devolução da terceira normal da face */
            const Point& getThirdNormal() const;

            /* Devolução das primeiras coordenadas de textura */
            const texture::Coordinates& getFirstTexture() const;

            /* Devolução das segundas coordenadas de textura */
            const texture::Coordinates& getSecondTexture() const;

            /* Devolução das terceiras coordenadas de textura */
            const texture::Coordinates& getThirdTexture() const;

            /* Rotação de uma face para ficar virada para o lado oposto */
            void turn();

            /* Leitura de um ponto através de um ficheiro */
            void read(std::ifstream& stream);

            /* Desenho de um ponto no modo imediato */
            void draw() const;

            /* Alimentação de um buffer para pontos para desenho em modo VBO */
            void feedBufferPoints(std::vector<float>& buffer) const;

            /* Alimentação de um buffer para normais para desenho em modo VBO */
            void feedBufferNormals(std::vector<float>& buffer) const;

            /* Alimentação de um buffer para coordenadas de textura para desenho em modo VBO */
            void feedBufferTexture(std::vector<float>& buffer) const;

            /* Define o operador de comparação de igualdade */
            bool operator==(const Face& face) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const Face& face) const;

            /* Operação de clonagem de uma face */
            Face clone() const;

            /* Converte o grupo num formato string */
            std::string toString() const;
    };
}
#endif
