#ifndef PATCH_HPP
#define PATCH_HPP

#include "../primitives/point.hpp"
#include "batch.hpp"
#include <vector>

/* Inicialização do namespace onde irá ser definida a classe de patch */
namespace patches
{
    /* Definição da classe que representa um patch */
    class Patch {

        private:

            /* Propriedades do objeto patch */
            std::vector<primitives::Point*> points;
            std::vector<Batch> index;
            utils::Matrix curve;
            int tesselation;

        public:

            /* Construtor padrão de um patch */
            Patch(utils::Matrix curve, int tesselation);

            /* Construtor através de um stream de um patch */
            Patch(utils::Matrix curve, int tesselation, std::ifstream& stream);

            /* Construtor através de um ficheiro de um patch */
            Patch(utils::Matrix curve, int tesselation, std::string path);

            /* Destrutor de um patch */
            ~Patch();

            /* Adição de um batch ao patch */
            void addBatch(Batch batch);

            /* Devolução da lista de batches de um patch */
            std::vector<Batch> getBatches() const;

            /* Adição de um ponto ao patch */
            void addPoint(primitives::Point point);

            /* Devolução da lista de pontos de um patch */
            std::vector<primitives::Point> getPoints() const;

            /* Definição da curva associada ao patch */
            void setCurve(utils::Matrix curve);

            /* Devolução da matriz de curva associada ao patch */
            utils::Matrix getCurve() const;

            /* Definição do nível de tesselation do patch */
            void setTesselation(int tesselation);

            /* Devolução do nível de tesselation do patch */
            int getTesselation() const;

            /* Construção de uma primitiva baseada no patch */
            primitives::Primitive build() const;

            /* Leitura de um patch vindo de um stream */
            void read(std::ifstream& stream);

            /* Leitura de um patch vindo de um ficheiro */
            void read(std::string path);

            /* Operação de comparação por igualdade de patches */
            bool operator==(const Patch& patch) const;

            /* Operação de comparação por desigualdade de patches */
            bool operator!=(const Patch& patch) const;

            /* Operação de clonagem de um patch */
            Patch clone() const;

            /* Transformação de um patch em formato string */
            std::string toString() const;
    };
}

#endif