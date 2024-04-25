#ifndef BATCH_HPP
#define BATCH_HPP

#include "../../../shared/inc/utils/matrix.hpp"
#include "../primitives/primitive.hpp"
#include <fstream>
#include <vector>

/* Inicialização do namespace onde irá ser definida a classe de patch */
namespace patches
{
    /* Definição da classe que representa um patch */
    class Batch {

        private:

            /* Propriedades do objeto batch */
            std::vector<int> index;

        public:

            /* Construtor padrão de um batch */
            Batch();

            /* Construtor de cópia de um batch */
            Batch(const Batch& batch);

            /* Construtor através de um ficheiro de um patch */
            Batch(std::ifstream& stream);

            /* Adição de um índice ao batch */
            void add(int index);

            /* Devolução da lista de índices de um batch */
            std::vector<int> getIndex() const;

            /* Construção de uma primitiva baseada no batch */
            void build(primitives::Primitive * primitive, int tesselation, utils::Matrix curve, std::vector<primitives::Point*> points);

            /* Leitura de um batch vindo de um ficheiro */
            void read(std::ifstream& stream);

            /* Acesso a um índice do batch */
            int& operator[](int index);

            /* Acesso a um índice do batch sem possibilidade de modificação */
            const int& operator[](int index) const;

            /* Operação de comparação por igualdade de batches */
            bool operator==(const Batch& batch) const;

            /* Operação de comparação por desigualdade de batches */
            bool operator!=(const Batch& batch) const;

            /* Operação de clonagem de um batch */
            Batch clone() const;

            /* Transformação de um batch em formato string */
            std::string toString() const;
    };
}

#endif