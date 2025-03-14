#ifndef FACE_HPP
#define FACE_HPP

#include "../../../shared/inc/geometry/face.hpp"
#include "point.hpp"
#include <unordered_map>

/* Inicialização do namespace usado para definir a classe face */
namespace primitives{

    /* Definição da classe face */
    class Face : public geometry::Face {
        
        private:

            /* Definição das propriedades da face */
            Point first, second, third;

        public:

            /* Construtor parametrizado de pontos com ordem */
            Face(Point first, Point second, Point third);

            /* Construtor de cópia de uma face */
            Face(const Face& face);

            /* Definição do primeiro ponto da face */
            void setFirst(Point point);

            /* Definição do segundo ponto da face */
            void setSecond(Point point);

            /* Definição do terceiro ponto da face */
            void setThird(Point point);

            /* Definição de todos os pontos da face */
            void setPoints(Point first, Point second, Point third);

            /* Devolução do primeiro ponto da face */
            const Point& getFirst() const;

            /* Devolução do segundo ponto da face */
            const Point& getSecond() const;

            /* Devolução do terceiro ponto da face */
            const Point& getThird() const;

            /* Definição da normal da face */
            void normal();

            /* Definição das normais da face através de um dicionário */
            void setNormal(std::unordered_map<std::string, Point> normalMap);

            /* Atualização do dicionário de normais através dos pontos das faces */
            void updateNormal(std::unordered_map<std::string, Point> * normalMap) const;

            /* Cálculo da normal para uma esfera */
            void sphereNormal();

            /* Cálculo da normal para a superfície de um cone */
            void coneNormal(float height, float radius);

            /* Cálculo da normal desta face */
            utils::Matrix getNormal() const;

            /* Cálculo das coordenadas de uma superfície plana */
            void surfaceCoordinates(float side);

            /* Cálculo das coordenadas de uma esfera */
            void sphereCoordinates(bool borderH);

            /* Cálculo das coordenadas de uma superfície lateral de cone */
            void coneCoordinates(float height, bool borderH);

            /* Normalização de todos os pontos de uma face */
            void normalize();

            /* Transformação de uma face dada uma matriz */
            void transform(const utils::Matrix& transform);

            /* Translação de uma face dado um vetor */
            void translateD(float dx, float dy, float dz);

            /* Translação de uma face dado um vetor polar */
            void translateP(float radius, float alpha, float beta);

            /* Rotação de uma face dado um eixo e ângulo de rotação */
            void rotate(float angle, float rx, float ry, float rz);

            /* Escala de uma face dado um vetor de escala */
            void scale(float sx, float sy, float sz);

            /* Rotação de uma face para ficar virada para o lado oposto */
            void turn();

            /* Escrita de uma face em ficheiro */
            void write(std::ofstream &ofstream) const;

            /* Operação de clonagem de uma face */
            Face clone() const;

            /* Transformação de uma face em formato string */
            std::string toString() const;
    };
}
#endif
