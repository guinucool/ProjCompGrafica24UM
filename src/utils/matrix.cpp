/* Inclusão do cabeçalho da classe */
#include "../../includes/utils/matrix.hpp"

/* Inclusão de librarias para funcionalidade do programa */
#include <stdexcept>

/* Declaração do namespace usado para definir esta classe */
namespace utils
{
    /* Verificar se as dimensões das matrizes são iguais */
    bool Matrix::equalDimension(const Matrix& matrix) const {
        return this->rows == matrix.rows && this->cols == matrix.cols;
    }

    /* Verificar se a posição introduzida está dentro dos limites da matriz */
    bool Matrix::outOfBounds(size_t row, size_t col) const {
        return row >= this->rows || col >= this->cols;
    }

    /* Soma de matrizes */
    Matrix Matrix::sum(const Matrix& other) const {

        /* Verifica se as dimensões das matrizes são compatíveis */
        if (!(this->equalDimension(other))) {
            throw std::runtime_error("addition of different shaped matrices");
        }

        /* Cria a matriz resultado que vai ser dada como output */
        Matrix result(this->rows, this->cols, 0.0f);

        /* Soma os elementos das matrizes */
        for (size_t i = 0; i < this->data.size(); ++i)
            result.data[i] = this->data[i] + other.data[i];
            
        /* Devolução do resultado obtido */
        return result;
    }

    /* Operação de multiplicação de matrizes */
    Matrix Matrix::mul(const Matrix& other) const {

        /* Verifica se as dimensões das matrizes são compatíveis */
        if (this->cols != other.rows) {
            throw std::runtime_error("multiplication of incompatible shaped matrices");
        }

        /* Inicializa a matriz resultado toda a zero */
        Matrix result(this->rows, other.cols, 0.0f);

        /* Multiplica as matrizes e origina um resultado */
        for (size_t i = 0; i < this->rows; i++) {

            for (size_t j = 0; j < other.cols; j++) {

                /* Criação do elemento na posição i,j */
                float sum = 0.0f;

                for (size_t k = 0; k < this->cols; k++)
                    sum += this->at(i, k) * other.at(k, j);

                result.at(i, j) = sum;
            }
        }

        /* Devolução do resultado obtido */
        return result;
    }

    /* Construtor parametrizado */
    Matrix::Matrix(size_t rows, size_t cols, float initialValue) {
        this->rows = rows;
        this->cols = cols;
        this->data = std::vector<float>(rows * cols, initialValue);
    }

    /* Construtor de cópia */
    Matrix::Matrix(const Matrix& matrix) {
        this->rows = matrix.rows;
        this->cols = matrix.cols;
        this->data = std::vector<float>(matrix.data);
    }

    /* Devolução da referência de um elemento de uma matriz numa certa posição */
    float& Matrix::at(size_t row, size_t col) {

        /* Verifica se o elemento pedido está no alcance do vetor */
        if (this->outOfBounds(row, col))
            throw std::out_of_range("indices out of range");

        /* Devolve o elemento na posição pedida */
        return this->data[row * cols + col];
    }

    /* Devolução da referência de um elemento de uma matriz numa certa posição sem possibilidade de alteração */
    const float& Matrix::at(size_t row, size_t col) const {
        return this->at(row, col);
    }

    /* Operação de negação da matriz */
    Matrix Matrix::operator-() const {

        /* Cria a matriz resultado que vai ser dada como output */
        Matrix result(this->rows, this->cols, 0.0f);

        /* Nega todos os elementos presentes na matriz */
        for (size_t i = 0; i < this->data.size(); ++i)
            result.data[i] = -this->data[i];

        /* Devolve o resultado da operação */
        return result;
    }

    /* Operação de soma de matrizes */
    Matrix Matrix::operator+(const Matrix& other) const {
        return this->sum(other);
    }

    /* Operação de subtração de matrizes */
    Matrix Matrix::operator-(const Matrix& other) const {
        return this->sum(-other);
    }

    /* Operação de multiplicação de matrizes */
    Matrix Matrix::operator*(const Matrix& other) const {
        return this->mul(other);
    }

    /* Operação de comparação de igualdade entre duas matrizes */
    bool Matrix::operator==(const Matrix& matrix) const {
        return this->data == matrix.data;
    }

    /* Operação de comparação de desigualdade entre duas matrizes */
    bool Matrix::operator!=(const Matrix& matrix) const {
        return this->data != matrix.data;
    }

    /* Operação de clonagem de uma matriz */
    Matrix Matrix::clone() {
        return Matrix(*this);
    }

    /* Transformação da matriz em string */
    std::string Matrix::toString() {

        /* Inicialização da string vazia */
        std::string matrix = "";

        /* Passa por todas as linhas da matriz */
        for (size_t i = 0; i < rows; ++i) {

            /* Passa por todas as colunas da matriz */
            for (size_t j = 0; j < cols; ++j)
                matrix += std::to_string(this->at(i, j)) + ' ';

            /* Guarda um newLine para a mudança de linha */
            matrix += '\n';
        }

        /* Devolução da string construída */
        return matrix;
    }
}