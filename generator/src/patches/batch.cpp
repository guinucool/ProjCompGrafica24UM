/* Inclusão do cabeçalho da definição de batch */
#include "../../inc/patches/batch.hpp"

/* Inclusão de livrarias necessárias à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace utilizado para a definição */
namespace patches
{
    /* Construtor padrão de um batch */
    Batch::Batch() {}

    /* Construtor de cópia de um batch */
    Batch::Batch(const Batch& batch) : index(batch.index) {}

    /* Construtor através de um ficheiro de um patch */
    Batch::Batch(std::ifstream& stream) {
        this->read(stream);
    }

    /* Adição de um índice ao batch */
    void Batch::add(int index) {

        /* Verifica se o limite de índices ainda não foi atingido */
        if (this->index.size() >= 16)
            throw std::out_of_range("current batch does not accept any more indexes");

        /* Adição do índice ao batch */
        this->index.push_back(index);
    }

    /* Devolução da lista de índices de um batch */
    std::vector<int> Batch::getIndex() const {
        return this->index;
    }

    /* Construção de uma primitiva baseada no batch */
    void Batch::build(primitives::Primitive * primitive, int tesselation, utils::Matrix curve, std::vector<primitives::Point> points) {

        /* Cálculo do intervalo de tesselation */
        float t = 1.0f / tesselation;

        /* Cálculo da matriz curvada para cálculo dos pontos */
        utils::Matrix curved = curve.surface()
    }

    /* Leitura de um batch vindo de um ficheiro */
    void Batch::read(std::ifstream& stream) {

        /* Variável placeholder para a leitura de índices */
        int index;

        /* Leitura dos vários índices presentes no batch */
        for (size_t i = 0; i < 16; i++) {

            /* Atribuição do valor lido à variável */
            stream >> index;

            /* Ignora a vírgula que separa os valores */
            if (i != 15)
                stream.ignore(1);

            /* Adição do índice lido ao batch */
            this->add(index);
        }
        
        /* Verfica se a leitura foi válida */
        if (stream.fail())
            throw std::invalid_argument("given patch file is invalid");
    }

    /* Acesso a um índice do batch */
    int& Batch::operator[](int index) {
        
        /* Verifica se o limite dos índices não foi excedido */
        if (index >= 16)
            throw std::out_of_range("given index is out of bounds");

        /* Acesso ao elemento no índice */
        return this->index[index];
    }

    /* Acesso a um índice do batch sem possibilidade de modificação */
    const int& Batch::operator[](int index) const {

        /* Verifica se o limite dos índices não foi excedido */
        if (index >= 16)
            throw std::out_of_range("given index is out of bounds");

        /* Acesso ao elemento no índice */
        return this->index[index];
    }

    /* Operação de comparação por igualdade de batches */
    bool Batch::operator==(const Batch& batch) const {
        return (this->index == batch.index);
    }

    /* Operação de comparação por desigualdade de batches */
    bool Batch::operator!=(const Batch& batch) const {
        return (this->index != batch.index);
    }

    /* Operação de clonagem de um batch */
    Batch Batch::clone() const {
        return Batch((*this));
    }

    /* Transformação de um batch em formato string */
    std::string Batch::toString() const {

        /* Criação da string que irá armazenar o resultado */
        std::string result = "";

        /* População da string com elementos */
        for (int index: this->index)
            result += index + ',';

        /* Devolução da string criada */
        return result;
    }
}