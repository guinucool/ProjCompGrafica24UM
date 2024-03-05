#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
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

            /* Soma de matrizes */
            Matrix sum(const Matrix& other) const;

            /* Operação de multiplicação de matrizes */
            Matrix mul(const Matrix& other) const;

            /* Devolução da referência de um elemento de uma matriz num certo índice */
            float& at(int index);

            /* Devolução da referência de um elemento de uma matriz numa certo índice sem possibilidade de alteração */
            const float& at(int index) const;

            /* Inicialização da matriz identidade */
            void initIdentity();

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

            /* Construtor de matriz de rotação sobre eixo x */
            static Matrix rotateX(float ax);

            /* Construtor de matriz de rotação sobre eixo y */
            static Matrix rotateY(float ay);

            /* Construtor de matriz de rotação sobre eixo z */
            static Matrix rotateZ(float az);

            /* Devolução da referência de um elemento de uma matriz numa certa posição */
            float& at(size_t row, size_t col);

            /* Devolução da referência de um elemento de uma matriz numa certa posição sem possibilidade de alteração */
            const float& at(size_t row, size_t col) const;

            /* Devolução do número de linhas de uma matriz */
            size_t getRows() const;

            /* Devolução do número de colunas de uma matriz */
            size_t getCols() const;

            /* Operação de negação da matriz */
            Matrix operator-() const;

            /* Operação de soma de matrizes */
            Matrix operator+(const Matrix& other) const;

            /* Operação de subtração de matrizes */
            Matrix operator-(const Matrix& other) const;

            /* Operação de multiplicação de matrizes */
            Matrix operator*(const Matrix& other) const;

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

            /* Transformação da matriz em string */
            std::string toString() const;
    };
}

#endif