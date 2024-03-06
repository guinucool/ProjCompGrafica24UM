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

            /* Construtor padrão de câmera */
            Window();

            /* Construtor parametrizado de câmera */
            Window(int width, int height);

            /* Construtor de cópia de câmera */
            Window(const Window& camera);

            /* Construtor através de um elemento xml */
            Window(tinyxml2::XMLElement * window);

            /* Devolução da referência da largura da janela */
            int& width();

            /* Devolução da referência da largura da janela sem possibilidade de alteração */
            const int& width() const;

            /* Devolução da referência da altura da janela */
            int& height();

            /* Devolução da referência da altura da janela sem possibilidade de alteração */
            const int& height() const;

            /* Leitura de uma janela através de um ficheiro xml */
            void read(tinyxml2::XMLElement * window);

            /* Define a câmera que vai ser usada no cenário */
            void defineCamera() const;

            /* Define a função que será usada para definir o tamanho da câmera */
            void shapeCamera(int weight, int height) const;

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