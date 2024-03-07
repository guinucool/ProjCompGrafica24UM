/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/projection/window.hpp"

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace onde irá ser definida a classe */
namespace projection
{
    /* Construtor padrão de janela */
    Window::Window() : width(800), height(800) {}

    /* Construtor parametrizado de janela */
    Window::Window(int width, int height) {
        this->setWidth(width);
        this->setHeight(height);
    }

    /* Construtor de cópia de janela */
    Window::Window(const Window& camera) : width(camera.width), height(camera.height) {}

    /* Construtor através de um elemento xml */
    Window::Window(tinyxml2::XMLElement * window) : width(800), height(800) {
        this->read(window);
    }

    /* Definição do valor da largura da janela */
    void Window::setWidth(int width) {

        /* Verifica se a largura é válida */
        if (width <= 0)
            throw std::invalid_argument("given width is invalid");
        
        /* Associação da propriedade */
        this->width = width;
    }

    /* Devolução do valor da largura da janela */
    int Window::getWidth() const {
        return this->width;
    }

    /* Devolução do valor da altura da janela */
    void Window::setHeight(int height) {

        /* Verifica se a altura é válida */
        if (height <= 0)
            throw std::invalid_argument("given height is invalid");
        
        /* Associação da propriedade */
        this->height = height;
    }

    /* Devolução do valor da altura da janela */
    int Window::getHeight() const {
        return this->height;
    }

    /* Leitura de uma janela através de um ficheiro xml */
    void Window::read(tinyxml2::XMLElement * window) {

        /* Verifica se a propriedade de janela é válida */
        if (window->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Inicialização de variáveis para armazenar as propriedades */
        int width = this->width, height = this->height;

        /* Obtenção dos atributos e verificação da existência deles */
        window->QueryIntAttribute("width", &width);
        window->QueryIntAttribute("height", &height);

        /* Associação das propriedades */
        this->setWidth(width);
        this->setHeight(height);
    }

    /* Define a janela que vai ser usada para representar o cenário */
    void Window::defineWindow() const {

        /* Define a posição da janela no ecrã */
        glutInitWindowPosition(100, 100);

        /* Define as dimensões iniciais da janela */
	    glutInitWindowSize(this->width, this->height);

        /* Define o nome da janela */
	    glutCreateWindow("Engine");
    }

    /* Define o operador de comparação de igualdade */
    bool Window::operator==(const Window& camera) const {
        return this->width == camera.width && this->height == camera.height;
    }

    /* Define o operador de comparação de desigualdade */
    bool Window::operator!=(const Window& camera) const {
        return this->width != camera.width || this->height != camera.height;
    }

    /* Define a operação de clonagem de uma câmera */
    Window Window::clone() const {
        return Window((*this));
    }

    /* Converte a câmera num formato string */
    std::string Window::toString() const {

        /* Inicialização da string vazia */
        std::string window = "";

        /* Construção da string pretendida */
        window += "DIM-(" + std::to_string(this->width) + ',' + std::to_string(this->height) + ')';

        /* Devolução da string construída */
        return window; 
    }
}
