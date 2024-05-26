#ifndef TEXTURE_TEXTURE_HPP
#define TEXTURE_TEXTURE_HPP

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../../../external/tinyxml2/tinyxml2.h"
#include <string>

/* Inicialização do namespace onde vai ser definida a classe de textura */
namespace texture
{
    /* Definição da classe de textura */
    class Texture {

        private:

            /* Propriedades da classe textura */
            std::string path;
            GLuint texture;

        public:

            /* Construtor de textura vazia */
            Texture();

            /* Construtor de cópia de textura */
            Texture(const Texture& texture);

            /* Construtor de textura vinda de um caminho */
            Texture(std::string path);

            /* Construtor de textura vinda de uma configuração XML */
            Texture(std::string directory, tinyxml2::XMLElement * texture);

            /* Definição de um caminho para a textura */
            void setPath(std::string path);
            
            /* Devolução do caminho para a textura */
            std::string getPath() const;

            /* Inicialização de uma textura para ser aplicada a uma primitiva */
            void apply() const;

            /* Leitura de uma primitiva vinda de um ficheiro */
            void load();

            /* Leitura de uma primitiva vinda de um ficheiro xml */
            void read(std::string directory, tinyxml2::XMLElement * texture);

            /* Define o operador de comparação de igualdade */
            bool operator==(const Texture& texture) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const Texture& texture) const;

            /* Operação de clonagem de uma cor */
            Texture clone() const;

            /* Transformação de uma cor em formato string */
            std::string toString() const;
    };
}

#endif