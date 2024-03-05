#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "face.hpp"
#include <list>
#include <fstream>

/* Inicialização do namespace onde a classe irá ser definida */
namespace primitives
{

    /* Definição da classe primitiva */
    class Primitive {

        private:
            
            /* Definição das propriedades da primitiva */
            std::list<Face> faces;
        
        public:

            /* Construtor padrão de primitiva */
            Primitive();

            /* Construtor de cópia de primitiva */
            Primitive(const Primitive& primitive);

            /* Construtor por leitura de ficheiro de primitiva */
            Primitive(std::ifstream& stream);

            /* Adicionar uma primitiva */
            void add(Primitive primitive);

            /* Adicionar uma face */
            void add(Face face);

            /* Adicionar um triângulo */
            void addTriangle(Point first, Point second, Point third);

            /* Adicionar um quadrado */
            void addSquare(Point first, Point second, Point third, Point forth);

            /* Transformação de uma primitiva dada uma matriz */
            void transform(const utils::Matrix& transform);

            /* Translação de uma primitiva dado um vetor */
            void translateD(float dx, float dy, float dz);

            /* Translação de uma primitiva dado um vetor polar */
            void translateP(float radius, float alpha, float beta);

            /* Rotação de uma primitiva dado o ângulo de rotação sobre cada eixo */
            void rotate(float ax, float ay, float az);
            
            /* Escrita de uma primitiva em ficheiro */
            void write(std::ofstream& stream) const;

            /* Leitura de uma primitiva vinda de um ficheiro */
            void read(std::ifstream& stream);

            /* Desenho de uma primitiva no modo imediato */
            void draw() const;

            /* Alimentação de um buffer para desenho em modo VBO */
            void feedBuffer(std::vector<float>& buffer) const;

            /* Operação de comparação por igualdade de primitivas */
            bool operator==(const Primitive& primitive) const;

            /* Operação de comparação por desigualdade de primitivas */
            bool operator!=(const Primitive& primitive) const;

            /* Operação de clonagem de uma primitiva */
            Primitive clone() const;

            /* Transformação de uma primitiva em formato string */
            std::string toString() const;
    };
}

#endif