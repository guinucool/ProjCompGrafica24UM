/* Inclusão do cabeçalho de definição da estrutura de face */
#include "../../inc/geometry/face.hpp"

/* Inicialização do namespace ao qual a classe pertence */
namespace geometry
{
    /* Construtor vazio padrão */
    Face::Face() {}

    /* Operação de comparação por igualdade de faces */
    bool Face::operator==(const Face& face) const {
        return (this->getFirst() == face.getFirst() && this->getSecond() == face.getSecond() && this->getThird() == face.getThird()) ||
               (this->getFirst() == face.getSecond() && this->getSecond() == face.getThird() && this->getThird() == face.getFirst()) ||
               (this->getFirst() == face.getThird() && this->getSecond() == face.getFirst() && this->getThird() == face.getSecond());
    }

    /* Operação de comparação por desigualdade de faces */
    bool Face::operator!=(const Face& face) const {
        return !((this->getFirst() == face.getFirst() && this->getSecond() == face.getSecond() && this->getThird() == face.getThird()) ||
                 (this->getFirst() == face.getSecond() && this->getSecond() == face.getThird() && this->getThird() == face.getFirst()) ||
                 (this->getFirst() == face.getThird() && this->getSecond() == face.getFirst() && this->getThird() == face.getSecond()));
    }

    /* Transformação de uma face em string */
    std::string Face::toString() const {

        /* Criação da string vazia */
        std::string result = "";

        /* Construção da string que irá representar a face */
        result += "1-" + this->getFirst().toString() + '\n';
        result += "2-" + this->getSecond().toString() + '\n';
        result += "3-" + this->getThird().toString() + '\n';

        /* Devolução da string construída */
        return result;
    }
};
