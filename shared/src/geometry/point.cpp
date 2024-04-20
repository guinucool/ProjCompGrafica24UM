/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/geometry/point.hpp"

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>
#include <cmath>

/* Inicialização do namespace ao qual a classe pertence */
namespace geometry
{

    /* Construtor vazio */
    Point::Point() {}

    /* Definição do valor das coordenadas de um ponto */
    void Point::setCoords(float x, float y, float z) {

        /* Associação das coordendas à respetiva posição no vetor */
        this->X() = x;
        this->Y() = y;
        this->Z() = z;
    }

    /* Definição do valor das coordenadas de um ponto */
    void Point::setPolarCoords(float radius, float alpha, float beta) {

        /* Verificação de validade do raio */
        if (radius < 0)
            std::invalid_argument("invalid radius given");

        /* Associação das coordendas à respetiva posição no vetor */
        this->X() = radius * cos(beta) * sin(alpha);
        this->Z() = radius * cos(beta) * cos(alpha);
        this->Y() = radius * sin(beta);
    }

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