#ifndef FACE_HPP
#define FACE_HPP

#include "point.hpp"
#include <fstream>
#include <string>

/* Inicialização do namespace usado para definir a classe face */
namespace primitives{

    /* Definição da classe face */
    class Face {
        
        private:

            /* Definição das propriedades da face */
            Point first, second, third;

        public:

            /* Construtor parametrizado de pontos com ordem */
            Face(Point first, Point second, Point third);

            /* Construtor de cópia de uma face */
            Face(const Face& face);

            /* Construtor de uma face através de um ficheiro */
            Face(std::ifstream &fstream);

            /* Definição do primeiro ponto da face */
            void setFirst(Point point);

            /* Definição do segundo ponto da face */
            void setSecond(Point point);

            /* Definição do terceiro ponto da face */
            void setThird(Point point);

            /* Definição de todos os pontos da face */
            void setPoints(Point first, Point second, Point third);

            /* Devolução do primeiro ponto da face */
            Point getFirst() const;

            /* Devolução do segundo ponto da face */
            Point getSecond() const;

            /* Devolução do terceiro ponto da face */
            Point getThird() const;

            /* Transformação de uma face dada uma matriz */
            void transform(const utils::Matrix& transform);

            /* Translação de uma face dado um vetor */
            void translateD(float dx, float dy, float dz);

            /* Translação de uma face dado um vetor polar */
            void translateP(float radius, float alpha, float beta);

            /* Rotação de uma face dado o ângulo de rotação sobre cada eixo */
            void rotate(float ax, float ay, float az);

            /* Rotação de uma face para ficar virada para o lado oposto */
            void turn();

            /* Escrita de uma face em ficheiro */
            void write(std::ofstream &ofstream) const;

            /* Leitura de uma face através de um ficheiro */
            void read(std::ifstream &ifstream);

            /* Desenho de uma face no modo imediato */
            void draw() const;

            /* Alimentação de um buffer para desenho em modo VBO */
            void feedBuffer(std::vector<float>& buffer) const;
            
            /* Operação de comparação por igualdade de faces */
            bool operator==(const Face& face) const;

            /* Operação de comparação por desigualdade de faces */
            bool operator!=(const Face& face) const;

            /* Operação de clonagem de uma face */
            Face clone() const;

            /* Transformação de uma face em formato string */
            std::string toString() const;
    };
}
#endif
