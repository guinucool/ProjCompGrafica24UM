/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/texture/texture.hpp"

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>
#include <IL/il.h>
#include <iostream>

/* Inicialização do namespace onde vai ser definida a classe de textura */
namespace texture
{
    /* Construtor de textura vazia */
    Texture::Texture() : texture(0), path() {}

    /* Construtor de cópia de textura */
    Texture::Texture(const Texture& texture) : texture(texture.texture), path(texture.path) { }

    /* Construtor de textura vinda de um caminho */
    Texture::Texture(std::string path) : texture(0), path(path) {}

    /* Construtor de textura vinda de uma configuração XML */
    Texture::Texture(std::string directory, tinyxml2::XMLElement * texture) : texture(0), path() {
        this->read(directory, texture);
    }

    /* Definição de um caminho para a textura */
    void Texture::setPath(std::string path) {
        this->path = path;
    }
    
    /* Devolução do caminho para a textura */
    std::string Texture::getPath() const {
        return this->path;
    }

    /* Inicialização de uma textura para ser aplicada a uma primitiva */
    void Texture::apply() const {
        glBindTexture(GL_TEXTURE_2D, this->texture);
    }

    /* Leitura de uma primitiva vinda de um ficheiro */
    void Texture::load() {

        /* Variáveis auxiliares à definição da imagem em memória */
        unsigned int image, width, height;
        unsigned char * data;

        /* Leitura da imagem */
        ilGenImages(1, &image);
        ilBindImage(image);

        /* Verifica se a textura existe */
        if (!ilLoadImage((ILstring)this->path.c_str()))
            throw std::invalid_argument("invalid texture path given");

        /* Associação de propriedades da imagem */
        width = ilGetInteger(IL_IMAGE_WIDTH);
        height = ilGetInteger(IL_IMAGE_HEIGHT);

        /* Verifica se a textura é uma imagem */
        if (!ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
            throw std::invalid_argument("invalid texture path given");
        
        /* Informação da imagem */
        data = ilGetData();

        /* Associação da imagem à textura */
        glGenTextures(1, &(this->texture));
        glBindTexture(GL_TEXTURE_2D, this->texture);

        /* Associação dos parâmetros */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        /* Associação da imagem */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    /* Leitura de uma primitiva vinda de um ficheiro xml */
    void Texture::read(std::string directory, tinyxml2::XMLElement * texture) {

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

        /* Definição da textura através do ficheiro */
        this->setPath(directory + mpath);
    }

    /* Define o operador de comparação de igualdade */
    bool Texture::operator==(const Texture& texture) const {
        return (this->texture == texture.texture && this->path == texture.path);
    }

    /* Define o operador de comparação de desigualdade */
    bool Texture::operator!=(const Texture& texture) const {
        return (this->texture != texture.texture || this->path != texture.path);
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
        texture += std::to_string(this->texture) + "\n";
        texture += this->path;

        /* Devolução da string construída */
        return texture;
    }
}