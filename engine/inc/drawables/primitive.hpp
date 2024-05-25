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
#include "../lighting/color.hpp"
#include "../texture/texture.hpp"
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
            lighting::Color diffuse;
            lighting::Color ambient;
            lighting::Color specular;
            lighting::Color emissive;
            float shininess;
            texture::Texture texture;
            GLuint buffer[3];

            /* Leitura da componente de cores vinda da configuração XML */
            void readColors(tinyxml2::XMLElement * colors);

        protected:

            /* Definição da cor difusa do objeto */
            void setDiffuse(lighting::Color color);

            /* Definição da cor ambiente do objeto */
            void setAmbient(lighting::Color color);

            /* Definição da cor especular do objeto */
            void setSpecular(lighting::Color color);

            /* Definição da cor emissiva do objeto */
            void setEmissive(lighting::Color color);

            /* Definição de uma das cores do objeto */
            void setColor(std::string type, lighting::Color color);

            /* Definição do shininess do objeto */
            void setShininess(float shininess);

            /* Definição da textura do objeto */
            void setTexture(std::string texture);
        
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

            /* Devolução da cor difusa do objeto */
            lighting::Color getDiffuse() const;

            /* Devolução da cor ambiente do objeto */
            lighting::Color getAmbient() const;

            /* Devolução da cor especular do objeto */
            lighting::Color getSpecular() const;

            /* Devolução da cor emisiva do objeto */
            lighting::Color getEmissive() const;

            /* Devolução da shininess do objeto */
            float getShininess() const;

            /* Devolução da textura do objeto */
            texture::Texture getTexture() const;

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