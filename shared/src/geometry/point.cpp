/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/geometry/point.hpp"

/* Inicialização do namespace ao qual a classe pertence */
namespace geometry
{

    /* Construtor vazio */
    Point::Point() {}

    /* Operação de comparação por igualdade de pontos */
    bool Point::operator==(const Point& point) const {
        return this->X() == point.X() && this->Y() == point.Y() && this->Z() == point.Z();
    }

    /* Operação de comparação por desigualdade de pontos */
    bool Point::operator!=(const Point& point) const {
        return this->X() != point.X() || this->Y() != point.Y() || this->Z() != point.Z();
    }

    /* Transformação de um ponto em formato string */
    std::string Point::toString() const {

        /* Inicialização da string vazia */
        std::string point = "";

        /* Construção da string que irá representar o ponto */
        point = "(" + std::to_string(this->X()) + "," + std::to_string(this->Y()) + "," + std::to_string(this->Z()) + ")";

        /* Devolução da string criada */
        return point;
    }
}