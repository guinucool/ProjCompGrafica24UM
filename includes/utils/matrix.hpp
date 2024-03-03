#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <cstddef>
#include <string>

namespace utils {

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

        public:
            
            /* Construtor parametrizado */
            Matrix(size_t rows, size_t cols, float initialValue);

            /* Construtor de cópia */
            Matrix(const Matrix& matrix);

            /* Devolução da referência de um elemento de uma matriz numa certa posição */
            float& at(size_t row, size_t col);

            /* Devolução da referência de um elemento de uma matriz numa certa posição sem possibilidade de alteração */
            const float& at(size_t row, size_t col) const;

            /* Operação de negação da matriz */
            Matrix operator-() const;

            /* Operação de soma de matrizes */
            Matrix operator+(const Matrix& other) const;

            /* Operação de subtração de matrizes */
            Matrix operator-(const Matrix& other) const;

            /* Operação de multiplicação de matrizes */
            Matrix operator*(const Matrix& other) const;

            /* Operação de comparação de igualdade entre duas matrizes */
            bool operator==(const Matrix& matrix) const;

            /* Operação de comparação de desigualdade entre duas matrizes */
            bool operator!=(const Matrix& matrix) const;

            /* Operação de clonagem de uma matriz */
            Matrix clone();

            /* Transformação da matriz em string */
            std::string toString();
    };
}

#endif