#ifndef LIGHT_HPP
#define LIGHT_HPP

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../../../external/tinyxml2/tinyxml2.h"
#include <string>

/* Inicialização do namespace usado para definir a classe luz */
namespace lighting
{
    /* Definição da classe luz */
    class Light {

        private:

            /* Indíce mais alto atual da luz usada */
            static GLenum light;

            /* Definição das propriedades da luz */
            float x, y, z;

        protected:

            /* Devolução da referência do valor da coordenada x da luz */
            float& X();

            /* Devolução da referência do valor da coordenada y da luz */
            float& Y();

            /* Devolução da referência do valor da coordenada z da luz */
            float& Z();

            /* Atribuição de um índice à luz */
            static GLenum fetchIndex();

        public:

            /* Construtor de luz vazia (inicializa na origem) */
            Light();

            /* Construtor de luz parametrizado */
            Light(float x, float y, float z);

            /* Construtor de cópia de uma luz */
            Light(const Light& light);

            /* Devolução do valor da coordenada x da luz  */
            const float& getX() const;

            /* Devolução do valor da coordenada y da luz */
            const float& getY() const;

            /* Devolução do valor da coordenada z da luz */
            const float& getZ() const;

            /* Leitura de uma luz através de um formato XML */
            virtual void read(tinyxml2::XMLElement * light) = 0;

            /* Ativação e desenho de uma luz */
            virtual void enable() = 0;

            /* Desativação de uma luz */
            static void disable();

            /* Define o operador de comparação de igualdade */
            bool operator==(const Light * light) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const Light * light) const;

            /* Operação de clonagem de uma luz */
            virtual Light * clone() const = 0;

            /* Transformação de uma luz em formato string */
            std::string toString() const;
    };
}

#endif
