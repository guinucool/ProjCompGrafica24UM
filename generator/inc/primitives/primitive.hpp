#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../../../shared/inc/geometry/primitive.hpp"
#include "face.hpp"
#include <list>

/* Inicialização do namespace onde a classe irá ser definida */
namespace primitives
{

    /* Definição da classe primitiva */
    class Primitive : public geometry::Primitive {

        private:
            
            /* Definição das propriedades da primitiva */
            std::list<Face> faces;
        
        public:

            /* Construtor padrão de primitiva */
            Primitive();

            /* Construtor de cópia de primitiva */
            Primitive(const Primitive& primitive);

            /* Adicionar uma primitiva */
            void add(Primitive primitive);

            /* Adicionar uma face */
            void add(Face face);

            /* Adicionar um triângulo */
            void addTriangle(Point first, Point second, Point third);

            /* Adicionar um quadrado */
            void addSquare(Point first, Point second, Point third, Point forth);

            /* Devolução de uma cópia da lista de faces da primitiva */
            std::list<Face> getFaces() const;

            /* Cálculo da normal de todos os pontos por interpolação */
            void interpolationNormal();

            /* Cálculo da normal de todos os pontos por Gouraud */
            void gouraudNormal();

            /* Cálculo da normal para uma esfera */
            void sphereNormal();

            /* Cálculo das coordenadas de uma superfície plana */
            void surfaceCoordinates(float side);

            /* Cálculo das coordenadas de uma esfera */
            void sphereCoordinates();

            /* Cálculo das coordenadas de uma superfície lateral de cone */
            void coneCoordinates(float height);

            /* Normalização de todos os pontos de uma primitiva */
            void normalize();

            /* Transformação de uma primitiva dada uma matriz */
            void transform(const utils::Matrix& transform);

            /* Translação de uma primitiva dado um vetor */
            void translateD(float dx, float dy, float dz);

            /* Translação de uma primitiva dado um vetor polar */
            void translateP(float radius, float alpha, float beta);

            /* Rotação de uma primitiva dado um eixo e ângulo de rotação */
            void rotate(float angle, float rx, float ry, float rz);

            /* Escala de uma primitiva dado um vetor de escala */
            void scale(float sx, float sy, float sz);

            /* Rotação de todas as faces de uma primitiva para ficarem viradas para o lado oposto */
            void turn();
            
            /* Escrita de uma primitiva em ficheiro */
            void write(std::ofstream& stream) const;

            /* Escrita de uma primitiva em ficheiro dado o caminho onde o ficheiro deverá ser guardado */
            void write(std::string path) const;

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