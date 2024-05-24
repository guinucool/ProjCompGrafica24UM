/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/lighting/color.hpp"

/* Inclusão de módulos necessário à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace ao qual a class pertence */
namespace lighting
{
    /* Verificação do intervalo de cores */
    bool Color::verifyColor(int color) {
        return color < 0 || color > MAX_COLOR;
    }

    /* Atribuição do parâmetro da cor vermelha */
    void Color::setRed(int red) {

        /* Verifica se a cor dada é valida */
        if (Color::verifyColor(red))
            throw std::out_of_range("given red color parameter is out of range");

        /* Associação de propriedades */
        this->red = (red  / 1.0f) / MAX_COLOR;
    }

    /* Atribuição do parâmetro da cor verde */
    void Color::setGreen(int green) {

        /* Verifica se a cor dada é valida */
        if (Color::verifyColor(green))
            throw std::out_of_range("given green color parameter is out of range");

        /* Associação de propriedades */
        this->green = (green  / 1.0f) / MAX_COLOR;
    }

    /* Atribuição do parâmetro da cor azul */
    void Color::setBlue(int blue) {

        /* Verifica se a cor dada é valida */
        if (Color::verifyColor(blue))
            throw std::out_of_range("given blue color parameter is out of range");

        /* Associação de propriedades */
        this->blue = (blue / 1.0f) / MAX_COLOR;
    }

    /* Atribuição do parâmetro da transparência */
    void Color::setAlpha(float alpha) {

        /* Verifica se a cor dada é valida */
        if (alpha < 0 || alpha > 1)
            throw std::out_of_range("given alpha parameter is out of range");

        /* Associação de propriedades */
        this->alpha = alpha;
    }

    /* Atribuição do tipo de cor */
    void Color::setType(GLenum type) {

        /* Averigua qual o tipo de cor a ser estabelecido */
        if (type == GL_DIFFUSE) {

            /* Atribuição das cores padrão */
            this->setRed(200);
            this->setGreen(200);
            this->setBlue(200);

        } else if (type == GL_SPECULAR) {

            /* Atribuição das cores padrão */
            this->setRed(0);
            this->setGreen(0);
            this->setBlue(0);

        } else if (type == GL_AMBIENT) {

            /* Atribuição das cores padrão */
            this->setRed(50);
            this->setGreen(50);
            this->setBlue(50);

        } else if (type == GL_EMISSION) {

            /* Atribuição das cores padrão */
            this->setRed(0);
            this->setGreen(0);
            this->setBlue(0);

        } 
        
        /* Caso o tipo de cor não exista */
        else
            throw std::invalid_argument("given color type is not valid");

        /* Atribuição do tipo */
        this->type = type;
    }

    /* Atribuição do tipo de cor através de uma string */
    void Color::setType(std::string type) {

        /* Tradução do texto para o seu respetivo tipo */
        if (type == "diffuse")
            this->setType(GL_DIFFUSE);
        else if (type == "specular")
            this->setType(GL_SPECULAR);
        else if (type == "ambient")
            this->setType(GL_AMBIENT);
        else if (type == "emissive")
            this->setType(GL_EMISSION);

        /* Caso o tipo de cor não exista */
        else
            throw std::invalid_argument("given color type is not valid");
    }

    /* Construtor de cor vazio */
    Color::Color() : red(0), green(0), blue(0), alpha(1), type(GL_EMISSION) {}

    /* Construtor padrão de uma cor de um certo tipo */
    Color::Color(GLenum type) : red(0), green(0), blue(0), alpha(1), type(GL_EMISSION) {
        this->setType(type);
    }

    /* Construtor de cor parametrizado */
    Color::Color(int red, int green, int blue, float alpha, GLenum type) : red(0), green(0), blue(0), alpha(1), type(GL_EMISSION) {

        /* Atribuição de verificação de propriedades */
        this->setType(type);
        this->setRed(red);
        this->setGreen(green);
        this->setBlue(blue);
        this->setAlpha(alpha);
    }

    /* Construtor de cópia de uma cor */
    Color::Color(const Color& color) : red(color.red), green(color.green), blue(color.blue), alpha(color.alpha), type(color.type) {}

    /* Construtor através de um configuração XML de uma cor */
    Color::Color(tinyxml2::XMLElement * color) : alpha(1.0f) {
        this->read(color);
    }

    /* Devolução do valor do parâmetro da cor vermelha  */
    float Color::getRed() const {
        return this->red;
    }

    /* Devolução do valor do parâmetro da cor verde */
    float Color::getGreen() const {
        return this->green;
    }

    /* Devolução do valor do parâmetro da cor azul */
    float Color::getBlue() const {
        return this->blue;
    }

    /* Devolução do valor do parâmetro de transparência */
    float Color::getAlpha() const {
        return this->alpha;
    }

    /* Devolução do valor do tipo da cor */
    GLenum Color::getType() const {
        return this->type;
    }

    /* Leitura de uma cor através de um formato XML */
    void Color::read(tinyxml2::XMLElement * color) {

        /* Verifica se a propriedade de luz é válida */
        if (color->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Variável de tipo da cor */
        std::string type = std::string(color->Value());

        /* Associação do tipo de cor */
        this->setType(type);

        /* Variáveis que irão armazenar os atributos */
        int red, green, blue;

        /* Obtenção dos atributos e verificação da existência deles */
        if (color->QueryIntAttribute("R", &red) || color->QueryIntAttribute("G", &green) || color->QueryIntAttribute("B", &blue))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação das propriedades */
        this->setRed(red);
        this->setGreen(green);
        this->setBlue(blue);

        /* Variável de armazenamento da transparência */
        float alpha = this->alpha;

        /* Obtenção do atributo, caso exista */
        color->QueryFloatAttribute("alpha", &alpha);

        /* Associação da transparência */
        this->setAlpha(alpha);
    }

    /* Ativação da cor para o próximo objeto que fôr desenhado */
    void Color::enable() const {

        /* Criação do array de cor */
        float color[4] = { this->red, this->green, this->blue, this->alpha };

        /* Atribuição da propriedade ao próximo objeto */
        glMaterialfv(GL_FRONT, this->type, color);
    }

    /* Define o operador de comparação de igualdade */
    bool Color::operator==(const Color& color) const {
        return ((this->red == color.red) && (this->green == color.green) && (this->blue == color.blue) && (this->alpha == color.alpha) && (this->type == type));
    }

    /* Define o operador de comparação de desigualdade */
    bool Color::operator!=(const Color& color) const {
        return ((this->red != color.red) || (this->green != color.green) || (this->blue != color.blue) || (this->alpha != color.alpha) || (this->type != type));
    }

    /* Operação de clonagem de uma cor */
    Color Color::clone() const {
        return Color((*this));
    }

    /* Transformação de uma cor em formato string */
    std::string Color::toString() const {

        /* Inicialização de uma string vazia */
        std::string color = "";

        /* Construção da string */
        color += "(" + std::to_string(this->type) + "," + std::to_string(this->red) + "," + std::to_string(this->green) + "," + std::to_string(this->blue) + "," + std::to_string(this->alpha) + ")";

        /* Devolução da string construída */
        return color;
    }
}