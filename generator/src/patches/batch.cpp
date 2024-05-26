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
                float x0; float y0; float z0; float ux0; float uy0; float uz0; float vx0; float vy0; float vz0;
                float x1; float y1; float z1; float ux1; float uy1; float uz1; float vx1; float vy1; float vz1;
                float x2; float y2; float z2; float ux2; float uy2; float uz2; float vx2; float vy2; float vz2;
                float x3; float y3; float z3; float ux3; float uy3; float uz3; float vx3; float vy3; float vz3;

                /* Cálculo das coordenadas */
                x.surface(u, v, &x0, &ux0, &vx0); y.surface(u, v, &y0, &uy0, &vy0); z.surface(u, v, &z0, &uz0, &vz0);
                x.surface(nu, v, &x1, &ux1, &vx1); y.surface(nu, v, &y1, &uy1, &vy1); z.surface(nu, v, &z1, &uz1, &vz1);
                x.surface(nu, nv, &x2, &ux2, &vx2); y.surface(nu, nv, &y2, &uy2, &vy2); z.surface(nu, nv, &z2, &uz2, &vz2);
                x.surface(u, nv, &x3, &ux3, &vx3); y.surface(u, nv, &y3, &uy3, &vy3); z.surface(u, nv, &z3, &uz3, &vz3);

                /* Criação dos vetores derivados */
                utils::Matrix u0(4, 1, 0.0f), v0(4, 1, 0.0f); u0[0] = ux0; u0[1] = uy0; u0[2] = uz0; v0[0] = vx0; v0[1] = vy0; v0[2] = vz0;
                utils::Matrix u1(4, 1, 0.0f), v1(4, 1, 0.0f); u1[0] = ux1; u1[1] = uy1; u1[2] = uz1; v1[0] = vx1; v1[1] = vy1; v1[2] = vz1;
                utils::Matrix u2(4, 1, 0.0f), v2(4, 1, 0.0f); u2[0] = ux2; u2[1] = uy2; u2[2] = uz2; v2[0] = vx2; v2[1] = vy2; v2[2] = vz2;
                utils::Matrix u3(4, 1, 0.0f), v3(4, 1, 0.0f); u3[0] = ux3; u3[1] = uy3; u3[2] = uz3; v3[0] = vx3; v3[1] = vy3; v3[2] = vz3;
                utils::Matrix n0 = (u0.crossVector(v0).normalize());
                utils::Matrix n1 = (u1.crossVector(v1).normalize());
                utils::Matrix n2 = (u2.crossVector(v2).normalize());
                utils::Matrix n3 = (u3.crossVector(v3).normalize());

                /* Criação dos pontos necessários */
                primitives::Point p0(x0, y0, z0), p1(x1, y1, z1), p2(x2, y2, z2), p3(x3, y3, z3);
                p0.setCoordinates(texture::Coordinates(u, v));
                p1.setCoordinates(texture::Coordinates(nu, v));
                p2.setCoordinates(texture::Coordinates(nu, nv));
                p3.setCoordinates(texture::Coordinates(u, nv));
                p0.setNormal(n0);
                p1.setNormal(n1);
                p2.setNormal(n2);
                p3.setNormal(n3);

                /* Criação dos pontos necessários */
                primitive->addSquare(p0, p1, p2, p3);
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