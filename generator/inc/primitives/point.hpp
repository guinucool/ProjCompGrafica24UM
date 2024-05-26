#ifndef POINT_HPP
#define POINT_HPP

#include "../../../shared/inc/utils/matrix.hpp"
#include "../../../shared/inc/geometry/point.hpp"
#include "../../../shared/inc/texture/coordinates.hpp"
#include <fstream>

/* Inicialização do namespace usado para definir a classe ponto */
namespace primitives
{
    /* Definição da classe ponto */
    class Point : public geometry::Point {

        private:

            /* Definição das propriedades do ponto */
            utils::Matrix coords;
            utils::Matrix normal;
            texture::Coordinates texture;

        public:

            /* Construtor de ponto vazio (inicializa na origem) */
            Point();

            /* Construtor parametrizado de ponto */
            Point(float x, float y, float z);

            /* Construtor de cópia de ponto */
            Point(const Point& point);

            /* Construtor de um ponto vindo de um ficheiro */
            Point(std::ifstream& stream);

            /* Construtor parametrizado de ponto para coordenadas polares */
            static Point polarPoint(float radius, float alpha, float beta);

            /* Devolução da referência do valor da coordenada x do ponto */
            float& X();

            /* Devolução da referência do valor da coordenada x do ponto sem possibilidade de alteração */
            const float& X() const;

            /* Devolução da referência do do valor da coordenada y do ponto */
            float& Y();

            /* Devolução da referência do valor da coordenada y do ponto sem possibilidade de alteração */
            const float& Y() const;

            /* Devolução da referência do do valor da coordenada z do ponto */
            float& Z();

            /* Devolução da referência do valor da coordenada z do ponto sem possibilidade de alteração */
            const float& Z() const;

            /* Devolução da matriz das coordenadas do ponto */
            utils::Matrix getCoords() const;

            /* Definição do vetor normal de um ponto */
            void setNormal(const utils::Matrix& normal);

            /* Atualização do vetor normal de um ponto */
            void updateNormal(const utils::Matrix& normal);

            /* Cálculo da normal para uma esfera */
            void sphereNormal();

            /* Devolução da matriz da normal do ponto */
            utils::Matrix getNormal() const;

            /* Definição das coordenadas de textura */
            void setCoordinates(const texture::Coordinates& coordinates);

            /* Cálculo das coordenadas de uma superfície plana */
            void surfaceCoordinates(float side);

            /* Cálculo das coordenadas de uma esfera */
            void sphereCoordinates(bool borderH);

            /* Cálculo das coordenadas de uma superfície lateral de cone */
            void coneCoordinates(float height, bool borderH);

            /* Definição das coordenadas de textura */
            texture::Coordinates getCoordinates() const;

            /* Normalização de um ponto para encaixar no espaço certo */
            void normalize();

            /* Transformação de um ponto dada uma matriz */
            void transform(const utils::Matrix& transform);

            /* Translação de um ponto dado um vetor */
            void translateD(float dx, float dy, float dz);

            /* Translação de um ponto dado um vetor polar */
            void translateP(float radius, float theta, float beta);

            /* Rotação de um ponto dado um eixo e ângulo de rotação */
            void rotate(float angle, float rx, float ry, float rz);

            /* Escala de um ponto dado um vetor de escala */
            void scale(float sx, float sy, float sz);

            /* Leitura de um ponto vindo de um ficheiro */
            void read(std::ifstream& stream);

            /* Escrita de um ponto em ficheiro */
            void write(std::ofstream& stream) const;

            /* Operação de clonagem de um ponto */
            Point clone() const;

            /* Transformação de um ponto em formato string para ser usado como chave */
            std::string stringKey() const;

            /* Transformação de um ponto em formato string */
            std::string toString() const;
    };
}

#endif
