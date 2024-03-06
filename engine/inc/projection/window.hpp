#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../../../external/tinyxml2/tinyxml2.h"
#include <string>

/* Inicialização do namespace onde a classe irá ser definida */
namespace projection
{

    /* Definição da classe janela */
    class Window {

        private:

            /* Definição das propriedades da janela */
            int width, height;
        
        public:

            /* Construtor padrão de janela */
            Window();

            /* Construtor parametrizado de janela */
            Window(int width, int height);

            /* Construtor de cópia de janela */
            Window(const Window& camera);

            /* Construtor através de um elemento xml */
            Window(tinyxml2::XMLElement * window);

            /* Definição do valor da largura da janela */
            void setWidth(int width);

            /* Devolução do valor da largura da janela */
            int getWidth() const;

            /* Devolução do valor da altura da janela */
            void setHeight(int heigh);

            /* Devolução do valor da altura da janela */
            int getHeight() const;

            /* Leitura de uma janela através de um ficheiro xml */
            void read(tinyxml2::XMLElement * window);

            /* Define a janela que vai ser usada para representar o cenário */
            void defineWindow() const;

            /* Define o operador de comparação de igualdade */
            bool operator==(const Window& camera) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const Window& camera) const;

            /* Define a operação de clonagem de uma câmera */
            Window clone() const;

            /* Converte a câmera num formato string */
            std::string toString() const;
    };
}

#endif