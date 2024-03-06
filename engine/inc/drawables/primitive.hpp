#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../../../shared/inc/geometry/primitive.hpp"
#include "face.hpp"
#include <list>

/* Inicialização do namespace onde a classe irá ser definida */
namespace drawables
{

    /* Definição da classe primitiva */
    class Primitive : public geometry::Primitive {

        private:
            
            /* Definição das propriedades da primitiva */
            std::list<Face> faces;
        
        public:

            /* Construtor padrão de primitiva */
            Primitive();

            /* Construtor de cópia de primitiva */
            Primitive(const Primitive& primitive);

            /* Construtor de primitiva através da leitura de ficheiro */
            Primitive(std::ifstream& stream);

            /* Construtor de primitiva através da leitura de ficheiro dado o seu caminho */
            Primitive(std::string path);

            /* Rotação de todas as faces de uma primitiva para ficarem viradas para o lado oposto */
            void turn();

            /* Leitura de uma primitiva vinda de um ficheiro */
            void read(std::ifstream& stream);

            /* Leitura de uma primitiva vinda de um ficheiro */
            void read(std::string path);

            /* Desenho de uma primitiva no modo imediato */
            void draw() const;

            /* Alimentação de um buffer para desenho em modo VBO */
            void feedBuffer(std::vector<float>& buffer) const;

            /* Operação de comparação por igualdade de primitivas */
            bool operator==(const Primitive& primitive) const;

            /* Operação de comparação por desigualdade de primitivas */
            bool operator!=(const Primitive& primitive) const;

            /* Operação de clonagem de uma primitiva */
            Primitive clone() const;

            /* Transformação de uma primitiva em formato string */
            std::string toString() const;
    };
}

#endif