/* Inclusão do cabeçalho da definição de batch */
#include "../../inc/patches/patch.hpp"

/* Inclusão de livrarias necessárias à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace para a definição */
namespace patches
{
    /* Construtor padrão de um patch */
    Patch::Patch(utils::Matrix curve, int tesselation) : curve(curve), tesselation(tesselation) {

        /* Verifica se a matriz de curva é válida */
        if (curve.getCols() != 4 || curve.getRows() != 4)
            throw std::invalid_argument("given curve matrix is invalid");

        /* Verifica se o nível de tesselation dado é válido */
        if (tesselation < 1)
            throw std::invalid_argument("given tesselation level is invalid");
    }

    /* Construtor através de um stream de um patch */
    Patch::Patch(utils::Matrix curve, int tesselation, std::ifstream& stream) : curve(curve), tesselation(tesselation) {

        /* Verifica se a matriz de curva é válida */
        if (curve.getCols() != 4 || curve.getRows() != 4)
            throw std::invalid_argument("given curve matrix is invalid");

        /* Verifica se o nível de tesselation dado é válido */
        if (tesselation < 1)
            throw std::invalid_argument("given tesselation level is invalid");

        /* Leitura e transformação do ficheiro */
        this->read(stream);
    }

    /* Construtor através de um ficheiro de um patch */
    Patch::Patch(utils::Matrix curve, int tesselation, std::string path) : curve(curve), tesselation(tesselation) {

        /* Verifica se a matriz de curva é válida */
        if (curve.getCols() != 4 || curve.getRows() != 4)
            throw std::invalid_argument("given curve matrix is invalid");

        /* Leitura e transformação do ficheiro */
        this->read(path);
    }

    /* Adição de um batch ao patch */
    void Patch::addBatch(Batch batch) {
        this->index.push_back(batch);
    }

    /* Devolução da lista de batches de um patch */
    std::vector<Batch> Patch::getBatches() const {
        return this->index;
    }

    /* Adição de um ponto ao patch */
    void Patch::addPoint(primitives::Point point) {
        this->points.push_back(point);
    }

    /* Devolução da lista de pontos de um patch */
    std::vector<primitives::Point> Patch::getPoints() const {
        return this->points;
    }

    /* Definição da curva associada ao patch */
    void Patch::setCurve(utils::Matrix curve) {
        
        /* Verifica se a matriz de curva é válida */
        if (curve.getCols() != 4 || curve.getRows() != 4)
            throw std::invalid_argument("given curve matrix is invalid");

        /* Associação da matriz de curva ao patch */
        this->curve = curve;
    }

    /* Devolução da matriz de curva associada ao patch */
    utils::Matrix Patch::getCurve() const {
        return this->curve;
    }

    /* Definição do nível de tesselation do patch */
    void Patch::setTesselation(int tesselation) {

        /* Verifica se o nível de tesselation dado é válido */
        if (tesselation < 1)
            throw std::invalid_argument("given tesselation level is invalid");

        /* Associação do nível de tesselation dado */
        this->tesselation = tesselation;
    }

    /* Devolução do nível de tesselation do patch */
    int Patch::getTesselation() const {
        return this->tesselation;
    }

    /* Construção de uma primitiva baseada no patch */
    primitives::Primitive Patch::build() const {

    }

    /* Leitura de um patch vindo de um stream */
    void Patch::read(std::ifstream& stream) {

        /* Número de pontos e batches a ser lidas */
        size_t batches;
        size_t points;

        /* Leitura do número de batches */
        stream >> batches;

        /* Leitura das várias batches */
        for (size_t i = 0; i < batches; i++) {

            /* Leitura e conversão de uma batch */
            Batch batch(stream);

            /* Associação da batch */
            this->addBatch(batch);
        }

        /* Leitura do número de pontos */
        stream >> points;

        /* Leitura dos vários pontos */
        for (size_t i = 0; i < points; i++) {

        }
    }

    /* Leitura de um patch vindo de um ficheiro */
    void Patch::read(std::string path) {

        /* Inicialização da stream de leitura */
        std::ifstream stream(path);

        /* Verifica se a stream existe e foi aberta */
        if (!(stream.is_open()))
            throw std::invalid_argument("given patch path is invalid");

        /* Leitura do ficheiro e conversão dos pontos e batches */
        this->read(stream);

        /* Fecho da stream de leitura */
        stream.close();
    }

    /* Operação de comparação por igualdade de patches */
    bool Patch::operator==(const Patch& patch) const {
        return (this->points == patch.points) && (this->index == patch.index) && (this->curve == patch.curve) && (this->tesselation == patch.tesselation);
    }

    /* Operação de comparação por desigualdade de patches */
    bool Patch::operator!=(const Patch& patch) const {
        return (this->points != patch.points) || (this->index != patch.index) || (this->curve != patch.curve) || (this->tesselation != patch.tesselation);
    }

    /* Operação de clonagem de um patch */
    Patch Patch::clone() const {
        return Patch((*this));
    }

    /* Transformação de um patch em formato string */
    std::string Patch::toString() const {

        /* Criação da string que irá armazenar o resultado */
        std::string result;

        /* População das batches */
        result += "batches:\n";

        for (Batch batch: this->index)
            result += batch.toString() + "\n";

        /* População dos pontos */
        result += "points:\n";

        for (primitives::Point point: this->points)
            result += point.toString() + "\n";

        /* População da matriz de curva */
        result += "curve:\n";
        result += this->curve.toString();
        
        /* População do nível de tesselation */
        result += "tesselation: " + std::to_string(this->tesselation) + "\n";

        /* Devolução da string construída */
        return result; 
    }
}