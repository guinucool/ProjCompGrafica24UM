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

    /* Verificar se a matriz é quadrada */
    bool Matrix::isSquare() const {
        return this->rows == this->cols;
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

    /* Operação de multiplicação de uma matriz a um escalar */
    Matrix Matrix::mul(float scalar) const {

        /* Inicializa a matriz resultado toda a zero */
        Matrix result(this->rows, this->cols, 0.0f);

        /* Multiplica todos os elementos da matriz e origina um resultado */
        for (size_t i = 0; i < this->rows; i++)
            for (size_t j = 0; j < this->cols; j++)
                result.at(i, j) = this->at(i, j) * scalar;

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

    /* Cálculo da posição atual do ponto numa curva */
    Matrix Matrix::curvePosition(float t) const {

        /* Criação da matriz de tempo */
        utils::Matrix T(1, 4, 0.0f);

        /* Cálculo da matriz temporal */
        T[0] = pow(t, 3);
        T[1] = pow(t, 2);
        T[2] = t;
        T[3] = 1;

        /* Cálculo da coordenada representada pela matriz atual */
        Matrix coord = T * (*this);

        /* Devolução do valor da coordenada calculada */
        return coord;
    }

    /* Cálculo da derivada atual do ponto numa curva */
    Matrix Matrix::curveDerivate(float t) const {

        /* Criação da matriz de tempo */
        utils::Matrix T(1, 4, 0.0f);

        /* Cálculo da matriz temporal */
        T[0] = 3 * pow(t, 2);
        T[1] = 2 * t;
        T[2] = 1;
        T[3] = 0;

        /* Cálculo da derivada representada pela matriz atual */
        Matrix deriv = T * (*this);

        /* Devolução do valor da derivada calculada */
        return deriv;
    }

    /* Cálculo da posição atual do ponto numa superfície curva */
    Matrix Matrix::surfacePosition(float u, float v) const {

        /* Criação da matriz de tempo horizontal */
        utils::Matrix T(4, 1, 0.0f);

        /* Cálculo da matriz temporal */
        T[0] = pow(v, 3);
        T[1] = pow(v, 2);
        T[2] = v;
        T[3] = 1;

        /* Cálculo da coordenada representada pela matriz atual */
        Matrix coord = this->curvePosition(u) * T;

        /* Devolução do valor da coordenada calculada */
        return coord;
    }

    /* Cálculo das derivadas atuais do ponto numa superfície curva */
    Matrix Matrix::surfaceDerivate(float u, float v) const {
        /* To be implemented */
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

    /* Construtor de matriz de rotação */
    Matrix Matrix::rotate(float angle, float rx, float ry, float rz) {

        /* Verifica se o vetor sobre o qual se executa a rotação é válido */
        if (rx == 0 && ry == 0 && rz == 0)
            throw std::runtime_error("given rotation vector is not valid");

        /* Caso o vetor tenha uma componente z negativa */
        if (rz < 0)
            angle = -angle;

        /* Cálculo do comprimento do vetor */
        float v = (float) sqrt(pow(rx, 2) + pow(ry, 2) + pow(rz, 2));

        /* Cálculo do comprimento do vetor rebatido no plano xz */
        float d = (float) sqrt(pow(rx,2) + pow(rz,2));

        /* Ângulo de rotação no eixo y */
        float alpha = 0;

        /* Ângulo de rotação no eixo x */
        float theta = asin(ry/v);

        /* Cálculo do ângulo de rotação no eixo y */
        if (d != 0)
            alpha = -asin(rx/d);

        /* Cálculo das matrizes de rotação */
        Matrix rotateX = Matrix::rotateX(theta);
        Matrix rotateY = Matrix::rotateY(alpha);
        Matrix rotateZ = Matrix::rotateZ(angle);

        /* Cálculo da matriz de rotação final */
        Matrix rotate = rotateY.inverse() * rotateX.inverse() * rotateZ * rotateX * rotateY;

        /* Devolução da matriz calculada */
        return rotate;
    }

    /* Construtor de matriz de escala */
    Matrix Matrix::scale(float sx, float sy, float sz) {

        /* Inicialização da matriz */
        Matrix matrix(4);

        /* Criação da matriz de escala */
        matrix.at(0,0) = sx;
        matrix.at(1,1) = sy;
        matrix.at(2,2) = sz;

        /* Devolução da matriz construída */
        return matrix;
    }

    /* Construtor de uma matriz de Up */
    Matrix Matrix::up() {

        /* Inicialização da matriz */
        Matrix up(1, 3, 0.0f);

        /* Criação da matriz de Up */
        up[1] = 1.0f;

        /* Devolução da matriz de Up */
        return up;
    }

    /* Construtor de uma matriz de Bezier */
    Matrix Matrix::bezier() {
        
        /* Inicialização da matriz */
        Matrix bezier(4);

        /* Criação da matriz de Bezier */
        bezier.at(0,0) = -1.0f; bezier.at(0,1) = 3.0f; bezier.at(0,2) = -3.0f; bezier.at(0,3) = 1.0f;
        bezier.at(1,0) = 3.0f; bezier.at(1,1) = -6.0f; bezier.at(1,2) = 3.0f; bezier.at(1,3) = 0.0f;
        bezier.at(2,0) = -3.0f; bezier.at(2,1) = 3.0f; bezier.at(2,2) = 0.0f; bezier.at(2,3) = 0.0f;
        bezier.at(3,0) = 1.0f; bezier.at(3,1) = 0.0f; bezier.at(3,2) = 0.0f; bezier.at(3,3) = 0.0f;

        /* Devolução da matriz de Bezier */
        return bezier;
    }

    /* Construtor de uma matriz de Catmull-Rom */
    Matrix Matrix::catmullRom() {

        /* Inicialização da matriz */
        Matrix catmull(4);

        /* Criação da matriz de Catmull-Rom */
        catmull.at(0,0) = -0.5f; catmull.at(0,1) = 1.5f; catmull.at(0,2) = -1.5f; catmull.at(0,3) = 0.5f;
        catmull.at(1,0) = 1.0f; catmull.at(1,1) = -2.5f; catmull.at(1,2) = 2.0f; catmull.at(1,3) = -0.5f;
        catmull.at(2,0) = -0.5f; catmull.at(2,1) = 0.0f; catmull.at(2,2) = 0.5f; catmull.at(2,3) = 0.0f;
        catmull.at(3,0) = 0.0f; catmull.at(3,1) = 1.0f; catmull.at(3,2) = 0.0f; catmull.at(3,3) = 0.0f;

        /* Devolução da matriz de Catmull-Rom */
        return catmull;
    }

    /* Devolução da referência de um elemento de uma matriz numa certa posição */
    float& Matrix::at(size_t row, size_t col) {

        /* Verifica se o elemento pedido está no alcance do vetor */
        if (this->outOfBounds(row, col))
            throw std::out_of_range("indices out of range");

        /* Devolve o elemento na posição pedida */
        return this->data[row * this->cols + col];
    }

    /* Devolução da referência de um elemento de uma matriz numa certa posição sem possibilidade de alteração */
    const float& Matrix::at(size_t row, size_t col) const {
        
        /* Verifica se o elemento pedido está no alcance do vetor */
        if (this->outOfBounds(row, col))
            throw std::out_of_range("indices out of range");

        /* Devolve o elemento na posição pedida */
        return this->data[row * this->cols + col];
    }

    /* Devolução do número de linhas de uma matriz */
    size_t Matrix::getRows() const {
        return this->rows;
    }

    /* Devolução do número de colunas de uma matriz */
    size_t Matrix::getCols() const {
        return this->cols;
    }

    /* Devolução do comprimento de uma matriz */
    size_t Matrix::getLength() const {
        return (this->rows * this->cols);
    }

    /* Corte de uma linha de uma matriz */
    Matrix Matrix::sliceRow(size_t row) const {

        /* Verificação da existência da linha */
        if (row >= this->rows)
            throw std::out_of_range("slice row out of bounds");

        /* Criação da matriz resultado */
        Matrix sliced(this->rows - 1, this->cols, 0);

        /* Colocação do corte da matriz original na matriz cortada */
        for (size_t rowIndex = 0; rowIndex < this->rows - 1; rowIndex++) {

            /* Indíce de linha da matriz original */
            size_t rowIndexOriginal = rowIndex;

            /* Caso a linha que se pretende cortar tenha sido atingida */
            if (rowIndex >= row)
                rowIndexOriginal++;

            /* Percorre as colunas para copiar os valores */
            for (size_t columnIndex = 0; columnIndex < this->cols; columnIndex++)
                sliced.at(rowIndex, columnIndex) = this->at(rowIndexOriginal, columnIndex);
        }
        
        /* Devolução da matriz cortada criada */
        return sliced;
    }

    /* Corte de uma coluna de uma matriz */
    Matrix Matrix::sliceColumn(size_t col) const {

        /* Verificação da existência da coluna */
        if (col >= this->cols)
            throw std::out_of_range("slice column out of bounds");

        /* Criação da matriz resultado */
        Matrix sliced(this->rows, this->cols - 1, 0);

        /* Colocação do corte da matriz original na matriz cortada */
        for (size_t rowIndex = 0; rowIndex < this->rows; rowIndex++) {

            /* Percorre as colunas para copiar os valores */
            for (size_t columnIndex = 0; columnIndex < this->cols - 1; columnIndex++) {

                /* Indíce de coluna da matriz original */
                size_t columnIndexOriginal = columnIndex;

                /* Caso a coluna que se pretende cortar tenha sido atingida */
                if (columnIndex >= col)
                    columnIndexOriginal++;

                sliced.at(rowIndex, columnIndex) = this->at(rowIndex, columnIndexOriginal);
            }
        }
        
        /* Devolução da matriz cortada criada */
        return sliced;
    }

    /* Corte de uma matriz */
    Matrix Matrix::slice(size_t row, size_t col) const {

        /* Corte da linha na matriz */
        Matrix slicedRow = this->sliceRow(row);

        /* Corte da linha na matriz */
        Matrix slicedColumn = slicedRow.sliceColumn(col);

        /* Devolução da matriz cortada final */
        return slicedColumn;
    }

    /* Cálculo do comprimento numérico de uma matriz */
    float Matrix::length() const {

        /* Acumulador de somas quadradas dos elementos da matriz */
        float sum = 0;

        /* Percorre os elementos todos e somas o seu quadrado */
        for (size_t i = 0; i < this->getLength(); i++)
            sum += pow((*this)[i], 2);

        /* Cálculo do comprimento numérico da matriz */
        float len = sqrt(sum);

        /* Devolução do comprimento calculado */
        return len;
    }

    /* Cálculo de um complemente algébrico de uma posição da matriz */
    float Matrix::cofactor(size_t row, size_t col) const {

        /* Verifica se a matriz da qual se pretende calcular o complemento algébrico é quadrada */
        if (!this->isSquare())
            throw std::runtime_error("given matrix does not have cofactors");

        /* Multiplicador do complemento */
        int multiplier = -1;

        /* Cálculo do multiplicador do complemento pretendido */
        multiplier = (int) pow(multiplier, row + col);

        /* Cálculo do complemento algébrico */
        float cofactor = multiplier * this->slice(row, col).determinant();

        /* Devolução do complemento calculado */
        return cofactor;
    }

    /* Cálculo do determinante de uma matriz */
    float Matrix::determinant() const {

        /* Verifica se a matriz da qual se pretende calcular o determinante é quadrada */
        if (!this->isSquare())
            throw std::runtime_error("given matrix does not have a determinant");

        /* Variável que irá armazenar o determinante */
        float determinant = 0;

        /* Caso seja pedido o determinante de uma matriz vazia */
        if (this->rows == 0)
            determinant = 1;

        /* Cálculo do determinante para a fatia atual */
        for (size_t row = 0; row < this->rows; row++)
            for (size_t col = 0; col < this->cols; col++)
                determinant += this->at(row, col) * this->cofactor(row, col);
        
        /* Devolução do determinante calculado */
        return determinant;
    }

    /* Curvamento de uma matriz dado um conjunto de pontos */
    void Matrix::curve(std::list<geometry::Point*> points, Matrix * xc, Matrix * yc, Matrix * zc) const {

        /* Verifica se o número de pontos dados é válido para uma curva */
        if (points.size() != 4)
            throw std::runtime_error("given point list is not valid for a curve");

        /* Criação das matrizes de coordenadas */
        Matrix x(1, 4, 0.0f);
        Matrix y(1, 4, 0.0f);
        Matrix z(1, 4, 0.0f);

        /* Iterador de população das matrizes de coordenadas */
        int index = 0;

        /* Iteração por todos os pontos do conjunto de pontos */
        for (geometry::Point * point: points) {

            /* Atribuição das coordenadas aos conjuntos */
            x[index] = point->X();
            y[index] = point->Y();
            z[index] = point->Z();

            /* Passagem para o próximo índice */
            index++;
        }
        
        /* Multiplicação da matriz do eixo x para criação de curvas */
        if (xc != NULL)
            *xc = (*this) * x;

        /* Multiplicação da matriz do eixo y para criação de curvas */
        if (yc != NULL)
            *yc = (*this) * y;

        /* Multiplicação da matriz do eixo z para criação de curvas */
        if (zc != NULL)
            *zc = (*this) * z;
    }

    /* Curvamento de uma matriz dado um intervalo de tempo */
    void Matrix::curve(float t, float * position, float * derivate) const {

        /* Verifica se a matriz é curvável */
        if (this->rows != 4 && this->cols != 1)
            throw std::runtime_error("given matrix is not valid to curve with an instant");

        /* Obtenção do valor de posição */
        if (position != NULL)
            *position = this->curvePosition(t)[0];

        /* Obtenção do valor de derivada */
        if (derivate != NULL)
            *derivate = this->curveDerivate(t)[0];
    }

    /* Curvamento de uma matriz dado um conjunto de pontos e um intervalo de tempo */
    void Matrix::curve(float t, std::list<geometry::Point*> points, Matrix * position, Matrix * derivate) const {

        /* Criação das matrizes de curva */
        Matrix x(1, 4, 0.0f);
        Matrix y(1, 4, 0.0f);
        Matrix z(1, 4, 0.0f);

        /* Criação das curvas dos eixos */
        this->curve(points, &x, &y, &z);

        /* Obtenção da matriz de posição */
        if (position != NULL) {

            /* Criação da matriz resultado */
            Matrix pos(3, 1, 0.0f);

            /* Cálculo das coordenadas */
            pos[0] = x.curvePosition(t)[0];
            pos[1] = y.curvePosition(t)[0];
            pos[2] = z.curvePosition(t)[0];

            /* Associação da matriz criada */
            *position = pos;
        }

        /* Obtenção da matriz de derivada */
        if (derivate != NULL) {

            /* Criação da matriz resultado */
            Matrix deriv(3, 1, 0.0f);

            /* Cálculo das coordenadas */
            deriv[0] = x.curveDerivate(t)[0];
            deriv[1] = y.curveDerivate(t)[0];
            deriv[2] = z.curveDerivate(t)[0];

            /* Associação da matriz criada */
            *derivate = deriv;
        }
    }

    /* Curvamento de uma matriz em superfície dado um conjunto de pontos */
    void Matrix::surface(std::list<geometry::Point*> points, Matrix * xs, Matrix * ys, Matrix * zs) const {

        /* Verifica se o número de pontos dados é válido para uma superfície */
        if (points.size() != 16)
            throw std::runtime_error("given point list is not valid for a curve");

        /* Criação das matrizes de coordenadas */
        Matrix x(4, 4, 0.0f);
        Matrix y(4, 4, 0.0f);
        Matrix z(4, 4, 0.0f);

        /* Iterador de população das matrizes de coordenadas */
        int index = 0;

        /* Iteração por todos os pontos do conjunto de pontos */
        for (geometry::Point * point: points) {

            /* Atribuição das coordenadas aos conjuntos */
            x[index] = point->X();
            y[index] = point->Y();
            z[index] = point->Z();

            /* Passagem para o próximo índice */
            index++;
        }

        /* Colocação das matrizes na posição correta */
        x = x.transpose();
        y = y.transpose();
        z = z.transpose();

        /* Cálculo da matriz de curva transposta */
        Matrix transposed = this->transpose();

        /* Multiplicação de matrizes para criação da matriz do eixo x */
        if (xs != NULL)
            *xs = (*this) * x * transposed;

        /* Multiplicação de matrizes para criação da matriz do eixo y */
        if (ys != NULL)
            *ys = (*this) * y * transposed;

        /* Multiplicação de matrizes para criação da matriz do eixo z */
        if (zs != NULL)
            *zs = (*this) * z * transposed;
    }

    /* Curvamento de uma matriz em superfície dado dois instantes */
    void Matrix::surface(float u, float v, float * position, float * derivate) const {

        /* Verifica se a matriz é curvável para superfície */
        if (this->rows != 4 && this->cols != 4)
            throw std::runtime_error("given matrix is not valid to curve with an instant");

        /* Obtenção do valor de posição */
        if (position != NULL)
            *position = this->surfacePosition(u, v)[0];

        /* Obtenção do valor de derivada */
        if (derivate != NULL)
            *derivate = this->surfaceDerivate(u, v)[0];
    }

    /* Curvamento de uma matriz em superfície dado um conjunto de pontos e dois instantes */
    void Matrix::surface(float u, float v, std::list<geometry::Point*> points, Matrix * position, Matrix * derivate) const {

        /* Criação das matrizes de superfície dos eixos */
        Matrix x(4, 4, 0.0f);
        Matrix y(4, 4, 0.0f);
        Matrix z(4, 4, 0.0f);

        /* Criação das superfícies dos eixos */
        this->surface(points, &x, &y, &z);

        /* Obtenção da matriz de posição */
        if (position != NULL) {

            /* Criação da matriz resultado */
            Matrix pos(3, 1, 0.0f);

            /* Cálculo das coordenadas */
            pos[0] = x.surfacePosition(u, v)[0];
            pos[1] = y.surfacePosition(u, v)[0];
            pos[2] = z.surfacePosition(u, v)[0];

            /* Associação da matriz criada */
            *position = pos;
        }

        /* Obtenção da matriz de derivada */
        if (derivate != NULL) {

            /* Criação da matriz resultado */
            Matrix deriv(3, 1, 0.0f);

            /* Cálculo das coordenadas */
            deriv[0] = x.surfaceDerivate(u, v)[0];
            deriv[1] = y.surfaceDerivate(u, v)[0];
            deriv[2] = z.surfaceDerivate(u, v)[0];

            /* Associação da matriz criada */
            *derivate = deriv;
        }
    }

    /* Cruzamento de duas matrizes tridimensionais */
    Matrix Matrix::cross(Matrix matrix) const {

        /* Verifica se o cruzamento de ambas as matrizes é possível */
        if (this->getLength() != 3 || matrix.getLength() != 3)
            throw std::runtime_error("given matrices can't be crossed");

        /* Criação da matriz cruzada */
        Matrix crossed(1, 3, 0);

        /* Cálculo dos valores da matriz cruzada */
        crossed[0] = (*this)[1] * matrix[2] - (*this)[2] * matrix[1];
        crossed[1] = (*this)[2] * matrix[0] - (*this)[0] * matrix[2];
        crossed[2] = (*this)[0] * matrix[1] - (*this)[1] * matrix[0];

        /* Devolução da matriz cruzada */
        return crossed;
    }

    /* Cálculo de uma matriz normalizada */
    Matrix Matrix::normalize() const {

        /* Normalizador da matriz */
        float normalizer = this->length();

        /* Criação de uma matriz para armazenar o resultado */
        Matrix normalized = (*this) * (1 / normalizer);

        /* Devolução da matriz normalizada */
        return normalized;        
    }

    /* Cálculo da matriz de complementos algébricos */
    Matrix Matrix::cofactors() const {

        /* Criação de uma nova matriz que corresponderá à matriz de complementos algébricos */
        Matrix cofactors(this->rows, this->cols, 0.0f);

        /* Criação dos complementos algébricos para os vários elementos */
        for (size_t row = 0; row < this->rows; row++)
            for (size_t col = 0; col < this->cols; col++)
                cofactors.at(row, col) = this->cofactor(row, col);

        /* Devolução da matriz de complementos algébricos criada */
        return cofactors;
    }

    /* Cálculo da matriz transposta */
    Matrix Matrix::transpose() const {

        /* Criação de uma nova matriz que corresponderá à transposta */
        Matrix transpose(this->rows, this->cols, 0.0f);

        /* Transposição e colocação dos elementos na nova matriz */
        for (size_t row = 0; row < this->rows; row++)
            for (size_t col = 0; col < this->cols; col++)
                transpose.at(col, row) = this->at(row, col);
        
        /* Devolução da matriz transposta criada */
        return transpose;
    }

    /* Cálculo da matriz adjacente */
    Matrix Matrix::adjacent() const {

        /* Criação da matriz de cofatores da matriz original */
        Matrix cofactors = this->cofactors();

        /* Criação da matriz adjacente da matriz original */
        Matrix adjacent = cofactors.transpose();

        /* Devolução da matriz adjacente criada */
        return adjacent;
    }

    /* Cálculo da inversa de uma matriz */
    Matrix Matrix::inverse() const {

        /* Verifica se a matriz da qual se pretende calcular a inversa é quadrada */
        if (!this->isSquare())
            throw std::runtime_error("given matrix does not have a inverse");

        /* Cálcula o determinante da matriz */
        float determinant = this->determinant();

        /* Verifica se o determinante da matriz da qual se pretende calcular a inversa é diferente de 0 */
        if (determinant == 0)
            throw std::runtime_error("given matrix does not have a inverse");

        /* Cálculo da inversa do determinante */
        float inv = 1 / determinant;

        /* Cálculo da matriz inversa */
        Matrix inverse = this->adjacent() * inv;

        /* Devolução da inversa calculada */
        return inverse;
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

    /* Operação de atribuição de valores de matrizes */
    Matrix& Matrix::operator=(const Matrix& other) {

        /* Atribuição das propriedades */
        this->rows = other.rows;
        this->cols = other.cols;

        /* Atribuição do conteúdo */
        this->data = other.data;

        /* Devolução do apontador da matriz com os valores atualizados */
        return (*this);
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

    /* Operação de multiplicação de matrizes a escalares */
    Matrix Matrix::operator*(float scalar) const {
        return this->mul(scalar);
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

    /* Transformação de uma matriz num array */
    float * Matrix::toArray() const {

        /* Criação do array onde vai ser armazenado o resultado */
        float * matrix = new float[this->getLength()];

        /* População do array com os valores da matriz */
        for (size_t i = 0; i < this->getLength(); i++)
            matrix[i] = (*this)[i];
        
        /* Devolução do apontador do array criado */
        return matrix;
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