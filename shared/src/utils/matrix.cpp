/* Inclusão do cabeçalho da classe */
#include "../../inc/utils/matrix.hpp"

/* Inclusão de librarias para funcionalidade do programa */
#include <stdexcept>
#include <cmath>

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

    /* Devolução da referência de um elemento de uma matriz num certo índice */
    float& Matrix::at(int index) {

        /* Verifica se o elemento pedido está no alcance do vetor */
        if (index >= this->data.size())
            throw std::out_of_range("index out of range");

        /* Devolve o elemento na posição pedida */
        return this->data[index];
    }

    /* Devolução da referência de um elemento de uma matriz numa certo índice sem possibilidade de alteração */
    const float& Matrix::at(int index) const {

        /* Verifica se o elemento pedido está no alcance do vetor */
        if (index >= this->data.size())
            throw std::out_of_range("index out of range");

        /* Devolve o elemento na posição pedida */
        return this->data[index];
    }

    /* Inicialização da matriz para transformações */
    void Matrix::initIdentity() {

        /* Colocação do estado inicial */
        for (size_t i = 0; i < this->rows; i++)
            this->at(i, i) = 1.0f;
    }

    /* Construtor parametrizado */
    Matrix::Matrix(size_t rows, size_t cols, float initialValue) : rows(rows), cols(cols), data(rows * cols, initialValue) {}

    /* Construtor parametrizado para matriz identidade */
    Matrix::Matrix(size_t dim) : rows(dim), cols(dim), data(dim * dim, 0.0f) {
        this->initIdentity();
    }

    /* Construtor de cópia */
    Matrix::Matrix(const Matrix& matrix) : rows(matrix.rows), cols(matrix.cols), data(matrix.data) {}

    /* Construtor de matriz de translação */
    Matrix Matrix::translateD(float dx, float dy, float dz) {

        /* Inicialização da matriz */
        Matrix matrix(4);

        /* Criação da matriz de translação */
        matrix.at(0, 3) = dx;
        matrix.at(1, 3) = dy;
        matrix.at(2, 3) = dz;

        /* Devolução da matriz construída */
        return matrix;
    }

    /* Construtor de matriz de translação por coordenadas polares */
    Matrix Matrix::translateP(float radius, float alpha, float beta) {

        /* Inicialização da matriz */
        Matrix matrix(4);

        /* Criação da matriz de translação */
        matrix.at(0, 3) = radius * cos(beta) * sin(alpha);
        matrix.at(2, 3) = radius * cos(beta) * cos(alpha);
        matrix.at(1, 3) = radius * sin(beta);

        /* Devolução da matriz construída */
        return matrix;
    }

    /* Construtor de matriz de rotação sobre o eixo x */
    Matrix Matrix::rotateX(float ax) {

        /* Inicialização da matriz */
        Matrix matrix(4);

        /* Criação da matriz de rotação */
        matrix.at(1, 1) = cos(ax);
        matrix.at(1, 2) = -sin(ax);
        matrix.at(2, 1) = sin(ax);
        matrix.at(2, 2) = cos(ax);

        /* Devolução da matriz construída */
        return matrix;
    }

    /* Construtor de matriz de rotação sobre o eixo y */
    Matrix Matrix::rotateY(float ay) {

        /* Inicialização da matriz */
        Matrix matrix(4);

        /* Criação da matriz de rotação */
        matrix.at(0, 0) = cos(ay);
        matrix.at(0, 2) = sin(ay);
        matrix.at(2, 0) = -sin(ay);
        matrix.at(2, 2) = cos(ay);

        /* Devolução da matriz construída */
        return matrix;
    }

    /* Construtor de matriz de rotação sobre o eixo z */
    Matrix Matrix::rotateZ(float az) {

        /* Inicialização da matriz */
        Matrix matrix(4);

        /* Criação da matriz de rotação */
        matrix.at(0, 0) = cos(az);
        matrix.at(0, 1) = -sin(az);
        matrix.at(1, 0) = sin(az);
        matrix.at(1, 1) = cos(az);

        /* Devolução da matriz construída */
        return matrix;
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
        
        /* Verifica se o elemento pedido está no alcance do vetor */
        if (this->outOfBounds(row, col))
            throw std::out_of_range("indices out of range");

        /* Devolve o elemento na posição pedida */
        return this->data[row * cols + col];
    }

    /* Devolução do número de linhas de uma matriz */
    size_t Matrix::getRows() const {
        return this->rows;
    }

    /* Devolução do número de colunas de uma matriz */
    size_t Matrix::getCols() const {
        return this->cols;
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

    /* Acesso a um índice da matriz */
    float& Matrix::operator[](int index) {
        return this->at(index);
    }

    /* Acesso a um índice da matriz sem possibilidade de modificação */
    const float& Matrix::operator[](int index) const {
        return this->at(index);
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
    Matrix Matrix::clone() const {
        return Matrix(*this);
    }

    /* Transformação da matriz em string */
    std::string Matrix::toString() const {

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