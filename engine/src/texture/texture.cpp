/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/texture/texture.hpp"

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>
#include <IL/il.h>

/* Inicialização do namespace onde vai ser definida a classe de textura */
namespace texture
{
    /* Construtor de textura vazia */
    Texture::Texture() : texture(0) {}

    /* Construtor de cópia de textura */
    Texture::Texture(const Texture& texture) : texture(texture.texture) {}

    /* Construtor de textura vinda de um caminho */
    Texture::Texture(std::string path) : texture(0) {
        this->load(path);
    }

    /* Construtor de textura vinda de uma configuração XML */
    Texture::Texture(std::string directory, tinyxml2::XMLElement * texture) : texture(0) {
        this->load(directory, texture);
    }

    /* Inicialização de uma textura para ser aplicada a uma primitiva */
    void Texture::load() const {
        glBindTexture(GL_TEXTURE_2D, this->texture);
    }

    /* Leitura de uma primitiva vinda de um ficheiro */
    void Texture::load(std::string path) {

        /* Variáveis auxiliares à definição da imagem em memória */
        unsigned int image, width, height;
        unsigned char * data;

        /* Leitura da imagem */
        ilGenImages(1, &image);
        ilBindImage(image);
        ilLoadImage(path.c_str());

        /* Associação de propriedades da imagem */
        width = ilGetInteger(IL_IMAGE_WIDTH);
        height = ilGetInteger(IL_IMAGE_HEIGHT);
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        data = ilGetData();

        /* Associação da imagem à textura */
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        /* Associação dos parâmetros */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        /* Associação da imagem */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    /* Leitura de uma primitiva vinda de um ficheiro xml */
    void Texture::load(std::string directory, tinyxml2::XMLElement * texture) {

        /* Verifica se a propriedade de primitiva é válida */
        if (texture->ChildElementCount() != 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Inicialização da variável que irá armazenar o caminho para a textura */
        const char * path;

        /* Obtenção do atributo e verificação da existência dele */
        if (texture->QueryStringAttribute("file", &path))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Transformação do atributo em string */
        std::string mpath(path);

        /* Leitura da textura através do ficheiro */
        this->load(directory + path);
    }

    /* Define o operador de comparação de igualdade */
    bool Texture::operator==(const Texture& texture) const {
        return (this->texture == texture.texture);
    }

    /* Define o operador de comparação de desigualdade */
    bool Texture::operator!=(const Texture& texture) const {
        return (this->texture != texture.texture);
    }

    /* Operação de clonagem de uma cor */
    Texture Texture::clone() const {
        return Texture((*this));
    }

    /* Transformação de uma cor em formato string */
    std::string Texture::toString() const {

        /* Inicialização de uma string resultado */
        std::string texture = "";

        /* Construção da string */
        texture += std::to_string(this->texture);

        /* Devolução da string construída */
        return texture;
    }
}