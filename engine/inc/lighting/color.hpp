#ifndef COLOR_HPP
#define COLOR_HPP

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../../../external/tinyxml2/tinyxml2.h"
#include <string>

/* Inicialização do namespace usado para definir a classe ponto */
namespace lighting
{
    /* Definição da classe ponto */
    class Color {

        private:

            /* Definição das propriedades da cor */
            float red, green, blue;
            float alpha;
            GLenum type;

        protected:

            /* Atribuição do parâmetro da cor vermelha */
            void setRed(float red);

            /* Atribuição do parâmetro da cor verde */
            void setGreen(float green);

            /* Atribuição do parâmetro da cor azul */
            void setBlue(float blue);

            /* Atribuição do parâmetro da transparência */
            void setAlpha(float alpha);

            /* Atribuição do tipo de cor */
            void setType(float type);

            /* Atribuição do tipo de cor através de uma string */
            void setType(std::string type);

        public:

            /* Construtor de cor vazio */
            Color();

            /* Construtor padrão de uma cor de um certo tipo */
            Color(GLenum type);

            /* Construtor de cor parametrizado */
            Color(float red, float green, float blue, float alpha, GLenum type);

            /* Construtor de cópia de uma cor */
            Color(const Color& color);

            /* Construtor através de um configuração XML de uma cor */
            Color(tinyxml2::XMLElement * color);

            /* Devolução do valor do parâmetro da cor vermelha  */
            float getRed() const;

            /* Devolução do valor do parâmetro da cor verde */
            float getGreen() const;

            /* Devolução do valor do parâmetro da cor azul */
            float getBlue() const;

            /* Devolução do valor do parâmetro de transparência */
            float getAlpha() const;

            /* Devolução do valor do tipo da cor */
            GLenum getType() const;

            /* Leitura de uma cor através de um formato XML */
            void read(tinyxml2::XMLElement * color);

            /* Ativação da cor para o próximo objeto que fôr desenhado */
            void enable() const;

            /* Define o operador de comparação de igualdade */
            bool operator==(const Color& color) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const Color& color) const;

            /* Operação de clonagem de uma cor */
            Color clone() const;

            /* Transformação de uma cor em formato string */
            std::string toString() const;
    };
}

#endif