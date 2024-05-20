/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/lighting/spot.hpp"

/* Inclusão de bibliotecas necessárias à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace usado para definir a classe luz */
namespace lighting
{
    /* Devolução da referência do valor da coordenada direcional x da luz */
    float& Spot::DirX() {
        return this->dirX;
    }

    /* Devolução da referência do valor da coordenada direcional y da luz */
    float& Spot::DirY() {
        return this->dirY;
    }

    /* Devolução da referência do valor da coordenada direcional z da luz */
    float& Spot::DirZ() {
        return this->dirZ;
    }

    /* Atribuição do ângulo de abertura da luz */
    void Spot::SetCutoff(float cutoff) {
        
        /* Verificação de validade da abertura do ângulo */
        if (cutoff < 0 || (cutoff > 90 && cutoff != 180))
            throw std::invalid_argument("given cutoff is invalid");

        /* Associação do ângulo de abertura */
        this->cutoff = cutoff;
    }

    /* Construtor de luz vazia (inicializa na origem) */
    Spot::Spot() : Light(), dirX(0), dirY(0), dirZ(0), cutoff(0) {}

    /* Construtor de luz parametrizado */
    Spot::Spot(float x, float y, float z, float dirX, float dirY, float dirZ, float cutoff) : Light(x, y, z), dirX(dirX), dirY(dirY), dirZ(dirZ), cutoff(cutoff) {}

    /* Construtor de cópia de uma luz */
    Spot::Spot(const Spot& spot) : Light(spot), dirX(spot.dirX), dirY(spot.dirY), dirZ(spot.dirZ), cutoff(spot.cutoff) {}

    /* Construtor de uma luz através de um formato XML */
    Spot::Spot(tinyxml2::XMLElement * spot) : Light(), dirX(0), dirY(0), dirZ(0), cutoff(0) {
        this->read(spot);
    }

    /* Devolução do valor da coordenada direcional x da luz  */
    const float& Spot::getDirX() const {
        return this->dirX;
    }

    /* Devolução do valor da coordenada direcional y da luz */
    const float& Spot::getDirY() const {
        return this->dirY;
    }

    /* Devolução do valor da coordenada direcional z da luz */
    const float& Spot::getDirZ() const {
        return this->dirZ;
    }

    /* Devolução do valor do ângulo da luz */
    const float& Spot::getCutoff() const {
        return this->cutoff;
    }

    /* Leitura de uma luz através de um formato XML */
    void Spot::read(tinyxml2::XMLElement * spot) {

        /* Verifica se a propriedade de luz é válida */
        if (spot->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Variáveis que irão armazenar os atributos */
        float x, y, z;

        /* Obtenção dos atributos e verificação da existência deles */
        if (spot->QueryFloatAttribute("posX", &x) || spot->QueryFloatAttribute("posY", &y) || spot->QueryFloatAttribute("posZ", &z))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação das propriedades */
        this->X() = x;
        this->Y() = y;
        this->Z() = z;

        /* Obtenção dos atributos e verificação da existência deles */
        if (spot->QueryFloatAttribute("dirX", &x) || spot->QueryFloatAttribute("dirY", &y) || spot->QueryFloatAttribute("dirZ", &z))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação das propriedades */
        this->dirX = x;
        this->dirY = y;
        this->dirZ = z;

        /* Variável que irá armazenar o atributo */
        float cutoff;

        /* Obtenção do atributo e verificação da existência dele */
        if (spot->QueryFloatAttribute("cutoff", &cutoff))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação da propriedade */
        this->SetCutoff(cutoff);
    }

    /* Ativação e desenho de uma luz */
    void Spot::enable() {

        
    }

    /* Define o operador de comparação de igualdade */
    bool Spot::operator==(const Light * light) const {

        /* Transforma a luz em foco de luz */
        Spot * spot = (Spot *) light;

        /* Verificação de igualdade */
        return ((Light::operator==(light)) && (spot->dirX == this->dirX) && (spot->dirY == this->dirY) && (spot->dirZ == this->dirZ) && (spot->cutoff == this->cutoff));
    }

    /* Define o operador de comparação de desigualdade */
    bool Spot::operator!=(const Light * light) const {

        /* Transforma a luz em foco de luz */
        Spot * spot = (Spot *) light;

        /* Verificação de igualdade */
        return ((Light::operator!=(light)) || (spot->dirX != this->dirX) || (spot->dirY != this->dirY) || (spot->dirZ != this->dirZ) || (spot->cutoff != this->cutoff));
    }

    /* Operação de clonagem de uma luz */
    Light * Spot::clone() const {
        return new Spot((*this));
    }

    /* Transformação de uma luz em formato string */
    std::string Spot::toString() const {
        
        /* Inicialização de uma string */
        std::string light = "(Spot-Light)";

        /* Construção da string */
        light += Light::toString();
        light += "(" + std::to_string(this->dirX) + "," + std::to_string(this->dirY) + "," + std::to_string(this->dirZ) + ")\n";
        light += std::to_string(this->cutoff);

        /* Devolução da string construída */
        return light;
    }
}