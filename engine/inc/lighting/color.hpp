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

/* Inicialização do namespace usado para definir a classe cor */
namespace lighting
{
    /* Definição da classe cor */
    class Color {

        private:

            /* Definição das propriedades da cor */
            float red, green, blue;
            float alpha;
            GLenum type;

            /* Verificação do intervalo de cores */
            static bool Color::verifyColor(int color);

        protected:

            /* Atribuição do parâmetro da cor vermelha */
            void setRed(int red);

            /* Atribuição do parâmetro da cor verde */
            void setGreen(int green);

            /* Atribuição do parâmetro da cor azul */
            void setBlue(int blue);

            /* Atribuição do parâmetro da transparência */
            void setAlpha(float alpha);

            /* Atribuição do tipo de cor */
            void setType(GLenum type);

            /* Atribuição do tipo de cor através de uma string */
            void setType(std::string type);

        public:

            /* Construtor de cor vazio */
            Color();

            /* Construtor padrão de uma cor de um certo tipo */
            Color(GLenum type);

            /* Construtor de cor parametrizado */
            Color(int red, int green, int blue, float alpha, GLenum type);

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