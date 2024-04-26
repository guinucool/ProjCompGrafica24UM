#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../../../shared/inc/geometry/primitive.hpp"
#include "../../../external/tinyxml2/tinyxml2.h"
#include "face.hpp"
#include <vector>
#include <list>

/* Inicialização do namespace onde a classe irá ser definida */
namespace drawables
{

    /* Definição da classe primitiva */
    class Primitive : public geometry::Primitive {

        private:
            
            /* Definição das propriedades da primitiva */
            std::list<Face> faces;
            GLuint buffer[1];
        
        public:

            /* Construtor padrão de primitiva */
            Primitive();

            /* Construtor de cópia de primitiva */
            Primitive(const Primitive& primitive);

            /* Construtor de primitiva através da leitura de ficheiro */
            Primitive(std::ifstream& stream);

            /* Construtor de primitiva através da leitura de ficheiro dado o seu caminho */
            Primitive(std::string path);

            /* Construtor de uma primitiva vinda de um ficheiro xml */
            Primitive(std::string directory, tinyxml2::XMLElement * model);

            /* Devolução de uma cópia da lista de faces da primitiva */
            std::list<Face> getFaces() const;

            /* Rotação de todas as faces de uma primitiva para ficarem viradas para o lado oposto */
            void turn();

            /* Leitura de uma primitiva vinda de um ficheiro */
            void read(std::ifstream& stream);

            /* Leitura de uma primitiva vinda de um ficheiro */
            void read(std::string path);

            /* Leitura de uma primitiva vinda de um ficheiro xml */
            void read(std::string directory, tinyxml2::XMLElement * model);

            /* Desenho de uma primitiva */
            void draw(bool immediate) const;

            /* Alimentação de um buffer para desenho em modo VBO */
            void feedBuffer();

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