/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/texture/coordinates.hpp"

/* Inclusão de módulos necessários à funcionalidade */
#include <cmath>

/* Inicialização do namespace usado para definir a classe */
namespace texture
{
    /* Construtor de coordenadas vazio */
    Coordinates::Coordinates() : x(0), y(0) {}

    /* Construtor de coordenadas parametrizado */
    Coordinates::Coordinates(float x, float y) : x(x), y(y) {}
    
    /* Construtor de cópia de coordenadas */
    Coordinates::Coordinates(const Coordinates& coordinates) : x(coordinates.x), y(coordinates.y) {}

    /* Construtor de coordenadas de textura através de um ficheiro */
    Coordinates::Coordinates(std::ifstream& stream) : x(0), y(0) {
        this->read(stream);
    }

    /* Devolução da referência do valor da coordenada x do ponto */
    float& Coordinates::X() {
        return this->x;
    }

    /* Devolução da referência do valor da coordenada x do ponto sem possibilidade de alteração */
    const float& Coordinates::X() const {
        return this->x;
    }

    /* Devolução da referência do do valor da coordenada y do ponto */
    float& Coordinates::Y() {
        return this->y;
    }

    /* Devolução da referência do valor da coordenada y do ponto sem possibilidade de alteração */
    const float& Coordinates::Y() const {
        return this->y;
    }

    /* Aplicação das coordenadas para uma superfície plana */
    void Coordinates::surface(float side, utils::Matrix coords) {

        /* Cálculo do canto da textura */
        float corner = -(side / 2);

        /* Cálculo das coordenadas */
        this->x = (coords[0] - corner) / side;
        this->y = -((coords[2] + corner) / side);
    }

    /* Aplicação das coordenadas para uma esfera */
    void Coordinates::sphere(utils::Matrix coords, bool borderH) {

        /* Cálculo do centro da esfera */
        utils::Matrix center(4, 1, 0.0f);
        center[3] = 1.0f;

        /* Cálculo do vetor normal */
        utils::Matrix normal = (coords - center).normalize();

        /* Ângulo em usado para calcular x */
        float xang = std::atan2(normal[0], normal[2]);

        /* Cálculo das coordenadas */
        this->x = (0.5f + (xang / (2 * M_PI)));
        this->y = -(0.5f + (std::asin(normal[1]) / (M_PI)));

        /* Verifica se a borda foi atingida */
        if (borderH || xang < 0)
            this->x += 1;
    }

    /* Aplicação das coordenadas para a lateral de um cone */
    void Coordinates::cone(float height, utils::Matrix coords, bool borderH) {

        /* Centro da circunferência */
        utils::Matrix center(4, 1, 1.0f);
        center[0] = 0;
        center[1] = coords[1];
        center[2] = 0;

        /* Vetor inicial do cone */
        utils::Matrix front(4, 1, 0.0f);
        front[2] = 1;

        /* Cálculo da direção com o centro */
        utils::Matrix normal = (coords - center).normalize();

        /* Ângulo em usado para calcular x */
        float xang = std::atan2(normal[0], normal[2]);

        /* Cálculo das coordenadas */
        this->x = (0.5f + (xang / (2 * M_PI)));
        this->y = (coords[1] / height);

        /* Verifica se é o último elemento */
        /*if (borderH || xang < 0)
            this->x += 1;*/
    }

    /* Leitura de coordenadas vindas de um ficheiro */
    void Coordinates::read(std::ifstream& stream) {

        /* Leitura do valor das duas coordenadas vindas de um ficheiro */
        stream.read(reinterpret_cast<char*>(&(this->x)), sizeof(float));
        stream.read(reinterpret_cast<char*>(&(this->y)), sizeof(float));

        /* Verfica se a leitura foi válida */
        if (stream.fail())
            throw std::invalid_argument("given 3d file is invalid");
    }

    /* Escrita de coordenadas em ficheiro */
    void Coordinates::write(std::ofstream& stream) const {

        /* Escrita do valor das coordenadas em ficheiro */
        stream.write(reinterpret_cast<const char*>(&(this->x)), sizeof(float));
        stream.write(reinterpret_cast<const char*>(&(this->y)), sizeof(float));

        /* Verifica se a escrita foi bem sucedida */
        if (stream.fail())
            std::runtime_error("failed to write to file");
    }

    /* Alimentação de um buffer para desenho em modo VBO */
    void Coordinates::feedBuffer(std::vector<float>& buffer) const {
        buffer.push_back(this->x);
        buffer.push_back(this->y);
    }

    /* Operação de comparação por igualdade de coordenadas */
    bool Coordinates::operator==(const Coordinates& coordinates) const {
        return (this->x == coordinates.x && this->y == coordinates.y);
    }

    /* Operação de comparação por desigualdade de coordenadas */
    bool Coordinates::operator!=(const Coordinates& coordinates) const {
        return (this->x != coordinates.x || this->y != coordinates.y);
    }

    /* Operação de clonagem das coordenadas */
    Coordinates Coordinates::clone() const {
        return Coordinates((*this));
    }

    /* Transformação das coordenadas em formato string */
    std::string Coordinates::toString() const {

        /* Inicialização de uma string vazia */
        std::string coordinates = "";

        /* Construção da string */
        coordinates += "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";

        /* Devolução da string construída */
        return coordinates;
    }
}