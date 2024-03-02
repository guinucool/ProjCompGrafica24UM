#include "includes/utils/matrix.hpp"

int main() {
    // Criando uma instância da classe Matrix dentro do namespace utils
    utils::Matrix<int> mat(2, 3, 5);

    // Usando métodos da classe
    mat.print();

    return 0;
}