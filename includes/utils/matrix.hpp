#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <stdexcept> // Para std::out_of_range


namespace utils {
    template<typename T>
    class Matrix {
    private:
        std::vector<T> data; // Armazena os elementos da matriz em um vetor linear
        size_t rows; // Número de linhas
        size_t cols; // Número de colunas

    public:
        // Construtor padrão
        Matrix(size_t rows, size_t cols, T initialValue = T()) : rows(rows), cols(cols), data(rows * cols, initialValue) {}

        // Acessa elemento da matriz (com verificação de limites)
        T& at(size_t row, size_t col) {
            if (row >= rows || col >= cols) {
                throw std::out_of_range("Matrix indices out of range");
            }
            return data[row * cols + col];
        }

        const T& at(size_t row, size_t col) const {
            if (row >= rows || col >= cols) {
                throw std::out_of_range("Matrix indices out of range");
            }
            return data[row * cols + col];
        }

        // Imprime a matriz
        void print() const {
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    std::cout << at(i, j) << " ";
                }
                std::cout << std::endl;
            }
        }

        // Operações Matriciais
        // Adição de Matrizes
        Matrix operator+(const Matrix& other) const {
            if (this->rows != other.cols || this->cols != other.cols) {
                throw std::invalid_argument("Matrices dimensions mismatch for addition");
            }

            Matrix result(rows, cols, T());
            for (size_t i = 0; i < this->data.size(); ++i) {
                result.data[i] = this->data[i] + other.data[i];
            }
            return result;
        }

        // Subtração de Matrizes
        Matrix operator-(const Matrix& other) const {
            if (this->rows != other.rows || this->cols != other.cols) {
                throw std::invalid_argument("Matrices dimensions mismatch for subtraction");
            }

            Matrix result(rows, cols, T());
            for (size_t i = 0; i < this->data.size(); ++i) {
                result.data[i] = this->data[i] - other.data[i];
            }
            return result;
        }

        // Multiplicação de Matrizes
        Matrix operator*(const Matrix& other) const {
            if (this->cols != other.rows) {
                throw std::invalid_argument("Matrices dimensions mismatch for multiplication");
            }

            Matrix result(this->rows, other.cols, T());
            for (size_t i = 0; i < this->rows; ++i) {
                for (size_t j = 0; j < other.cols; ++j) {
                    T sum = T();
                    for (size_t k = 0; k < this->cols; ++k) {
                        sum += this->at(i, k) * other.at(k, j);
                    }
                    result.at(i, j) = sum;
                }
            }
            return result;
        }
    };
}
#endif