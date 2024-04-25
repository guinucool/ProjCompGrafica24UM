/* Inclusão do cabeçalho da definição de batch */
#include "../../inc/patches/batch.hpp"

/* Inclusão de livrarias necessárias à funcionalidade */
#include "../../../shared/inc/geometry/point.hpp"
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
    void Batch::build(primitives::Primitive * primitive, int tesselation, utils::Matrix curve, std::vector<primitives::Point*> points) {

        /* Cálculo do intervalo de tesselation */
        float t = 1.0f / tesselation;

        /* Matrizes de superfície de cada eixo */
        utils::Matrix x(4);
        utils::Matrix y(4);
        utils::Matrix z(4);

        /* Criação da lista de pontos para a superfície */
        std::list<geometry::Point*> surface;

        /* População da lista de pontos */
        for (int i : this->index)
            surface.push_back(points[i]);

        /* Criação das matrizes de superfície */
        curve.surface(surface, &x, &y, &z);
        
        /* Cálculo de pontos na superfície */
        for (float u = 1.0f; u > 0.0f; u -= t) {

            /* Cálculo de pontos na vertical */
            for (float v = 1.0f; v > 0.0f; v -= t) {
                
                /* Próximos instantes */
                float nu = u - t;
                float nv = v - t;

                /* Criação das várias coordenadas */
                float x0; float y0; float z0;
                float x1; float y1; float z1;
                float x2; float y2; float z2;
                float x3; float y3; float z3;

                /* Cálculo das coordenadas */
                x.surface(u, v, &x0, NULL); y.surface(u, v, &y0, NULL); z.surface(u, v, &z0, NULL);
                x.surface(nu, v, &x1, NULL); y.surface(nu, v, &y1, NULL); z.surface(nu, v, &z1, NULL);
                x.surface(nu, nv, &x2, NULL); y.surface(nu, nv, &y2, NULL); z.surface(nu, nv, &z2, NULL);
                x.surface(u, nv, &x3, NULL); y.surface(u, nv, &y3, NULL); z.surface(u, nv, &z3, NULL);

                /* Criação dos pontos necessários */
                primitive->addSquare(primitives::Point(x0, y0, z0), primitives::Point(x1, y1, z1), primitives::Point(x2, y2, z2), primitives::Point(x3, y3, z3));
            }
        }
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