#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../../inc/geometry/point.hpp"
#include <vector>
#include <list>
#include <cstddef>
#include <string>

/* Inicialização do namespace usado para definir as classes */
namespace utils
{
    /* Definição da classe que representa uma matriz */
    class Matrix {

        private:

            /* Propriedades do objeto matriz */
            std::vector<float> data; /* Vetor que representa a matriz */
            size_t rows;
            size_t cols;

            /* Verificar se as dimensões das matrizes são iguais */
            bool equalDimension(const Matrix& matrix) const;

            /* Verificar se a posição introduzida está dentro dos limites da matriz */
            bool outOfBounds(size_t row, size_t col) const;

            /* Verificar se a matriz é quadrada */
            bool isSquare() const;

            /* Soma de matrizes */
            Matrix sum(const Matrix& other) const;

            /* Operação de multiplicação de matrizes */
            Matrix mul(const Matrix& other) const;

            /* Operação de multiplicação de uma matriz a um escalar */
            Matrix mul(float scalar) const;

            /* Devolução da referência de um elemento de uma matriz num certo índice */
            float& at(int index);

            /* Devolução da referência de um elemento de uma matriz numa certo índice sem possibilidade de alteração */
            const float& at(int index) const;

            /* Inicialização da matriz identidade */
            void initIdentity();

            /* Construtor de matriz de rotação sobre eixo x */
            static Matrix rotateX(float ax);

            /* Construtor de matriz de rotação sobre eixo y */
            static Matrix rotateY(float ay);

            /* Construtor de matriz de rotação sobre eixo z */
            static Matrix rotateZ(float az);

            /* Cálculo da posição atual do ponto numa curva */
            Matrix curvePosition(float t) const;

            /* Cálculo da derivada atual do ponto numa curva */
            Matrix curveDerivate(float t) const;

            /* Cálculo da posição atual do ponto numa superfície curva */
            Matrix surfacePosition(float u, float v) const;

            /* Cálculo das derivadas atuais do ponto numa superfície curva */
            Matrix surfaceDerivate(float u, float v) const;

        public:
            
            /* Construtor parametrizado */
            Matrix(size_t rows, size_t cols, float initialValue);

            /* Construtor parametrizado para matriz identidade */
            Matrix(size_t dim);

            /* Construtor de cópia */
            Matrix(const Matrix& matrix);

            /* Construtor de matriz de translação */
            static Matrix translateD(float dx, float dy, float dz);

            /* Construtor de matriz de translação por coordenadas polares */
            static Matrix translateP(float radius, float theta, float beta);

            /* Construtor de matriz de rotação */
            static Matrix rotate(float angle, float rx, float ry, float rz);

            /* Construtor de matriz de escala */
            static Matrix scale(float sx, float sy, float sz);

            /* Construtor de uma matriz de Up */
            static Matrix up();

            /* Construtor de uma matriz de Bezier */
            static Matrix bezier();

            /* Construtor de uma matriz de Catmull-Rom */
            static Matrix catmullRom();

            /* Devolução da referência de um elemento de uma matriz numa certa posição */
            float& at(size_t row, size_t col);

            /* Devolução da referência de um elemento de uma matriz numa certa posição sem possibilidade de alteração */
            const float& at(size_t row, size_t col) const;

            /* Devolução do número de linhas de uma matriz */
            size_t getRows() const;

            /* Devolução do número de colunas de uma matriz */
            size_t getCols() const;

            /* Devolução do comprimento de uma matriz */
            size_t getLength() const;

            /* Corte de uma linha de uma matriz */
            Matrix sliceRow(size_t row) const;

            /* Corte de uma coluna de uma matriz */
            Matrix sliceColumn(size_t col) const;

            /* Corte de uma matriz */
            Matrix slice(size_t row, size_t col) const;

            /* Cálculo do comprimento numérico de uma matriz */
            float length() const;

            /* Cálculo de um complemente algébrico de uma posição da matriz */
            float cofactor(size_t row, size_t col) const;

            /* Cálculo do determinante de uma matriz */
            float determinant() const;

            /* Cruzamento pontual de duas matrizes */
            float dot(Matrix matrix) const;

            /* Curvamento de uma matriz dado um conjunto de pontos */
            void curve(std::list<geometry::Point*> points, Matrix * x, Matrix * y, Matrix * z) const;

            /* Curvamento de uma matriz dado um intervalo de tempo */
            void curve(float t, float * position, float * derivate) const;

            /* Curvamento de uma matriz dado um conjunto de pontos e um intervalo de tempo */
            void curve(float t, std::list<geometry::Point*> points, Matrix * position, Matrix * derivate) const;

            /* Curvamento de uma matriz em superfície dado um conjunto de pontos */
            void surface(std::list<geometry::Point*> points, Matrix * xs, Matrix * ys, Matrix * zs) const;

            /* Curvamento de uma matriz em superfície dado dois instantes */
            void surface(float u, float v, float * position, float * derivate) const;

            /* Curvamento de uma matriz em superfície dado um conjunto de pontos e dois instantes */
            void surface(float u, float v, std::list<geometry::Point*> points, Matrix * position, Matrix * derivate) const;

            /* Cruzamento de duas matrizes tridimensionais */
            Matrix cross(Matrix matrix) const;

            /* Cruzamento de dois vetores */
            Matrix crossVector(Matrix matrix) const;

            /* Cálculo de uma matriz normalizada */
            Matrix normalize() const;

            /* Cálculo da matriz de complementos algébricos */
            Matrix cofactors() const;

            /* Cálculo da matriz transposta */
            Matrix transpose() const;

            /* Cálculo da matriz adjacente */
            Matrix adjacent() const;

            /* Cálculo da inversa de uma matriz */
            Matrix inverse() const;

            /* Operação de negação da matriz */
            Matrix operator-() const;

            /* Operação de atribuição de valores de matrizes */
            Matrix& operator=(const Matrix& other);

            /* Operação de soma de matrizes */
            Matrix operator+(const Matrix& other) const;

            /* Operação de subtração de matrizes */
            Matrix operator-(const Matrix& other) const;

            /* Operação de multiplicação de matrizes */
            Matrix operator*(const Matrix& other) const;

            /* Operação de multiplicação de matrizes a escalares */
            Matrix operator*(float scalar) const;

            /* Acesso a um índice da matriz */
            float& operator[](int index);

            /* Acesso a um índice da matriz sem possibilidade de modificação */
            const float& operator[](int index) const;

            /* Operação de comparação de igualdade entre duas matrizes */
            bool operator==(const Matrix& matrix) const;

            /* Operação de comparação de desigualdade entre duas matrizes */
            bool operator!=(const Matrix& matrix) const;

            /* Operação de clonagem de uma matriz */
            Matrix clone() const;

            /* Transformação de uma matriz num array */
            float * toArray() const;

            /* Transformação da matriz em string */
            std::string toString() const;
    };
}

#endif