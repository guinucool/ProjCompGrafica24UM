/* Inclusão do cabeçalho da definição de primitiva */
#include "../../inc/drawables/primitive.hpp"

/* Inicialização do namespace utilizado para a definição */
namespace drawables
{
    /* Leitura da componente de cores vinda da configuração XML */
    void Primitive::readColors(tinyxml2::XMLElement * colors) {

        /* Verifica se a propriedade de cores é válida */
        if (colors->ChildElementCount() > 5)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Fixa o número de iterações */
        int children = colors->ChildElementCount();

        /* Leitura da lista de pontos */
        for (int i = 0; i < children; i++) {

            /* Vai buscar o primeiro elemento */
            tinyxml2::XMLElement * next = colors->FirstChildElement();

            /* Armazena o nome do primeiro elemento */
            std::string name = std::string(next->Value());

            /* Verifica qual é o elemento */
            if (name == "shininess") {
                
                /* Inicialização da variável que irá armazenar o atributo */
                float shininess;

                /* Obtenção do atributo e verificação da existência dele */
                if (next->QueryFloatAttribute("value", &shininess))
                    throw std::invalid_argument("given xml configuration is invalid");

                /* Atribuição da propriedade */
                this->setShininess(shininess);

            }
            
            /* Caso o elemento seja uma cor */
            else
                this->setColor(name, lighting::Color(next));

            /* Apaga o elemento lido */
            colors->DeleteChild(next);
        }
    }

    /* Definição da cor difusa do objeto */
    void Primitive::setDiffuse(lighting::Color color) {

        /* Verifica se a cor atribuída é da componente correta */
        if (color.getType() != GL_DIFFUSE)
            throw std::invalid_argument("given diffuse color is of wrong type");

        /* Associação da propriedade */
        this->diffuse = color;
    }

    /* Definição da cor ambiente do objeto */
    void Primitive::setAmbient(lighting::Color color) {

        /* Verifica se a cor atribuída é da componente correta */
        if (color.getType() != GL_AMBIENT)
            throw std::invalid_argument("given ambient color is of wrong type");

        /* Associação da propriedade */
        this->ambient = color;
    }

    /* Definição da cor especular do objeto */
    void Primitive::setSpecular(lighting::Color color) {

        /* Verifica se a cor atribuída é da componente correta */
        if (color.getType() != GL_SPECULAR)
            throw std::invalid_argument("given specular color is of wrong type");

        /* Associação da propriedade */
        this->specular = color;
    }

    /* Definição da cor emissiva do objeto */
    void Primitive::setEmissive(lighting::Color color) {

        /* Verifica se a cor atribuída é da componente correta */
        if (color.getType() != GL_EMISSION)
            throw std::invalid_argument("given emissive color is of wrong type");

        /* Associação da propriedade */
        this->emissive = color;
    }

    /* Definição de uma das cores do objeto */
    void Primitive::setColor(std::string type, lighting::Color color) {

        /* Averigua qual o tipo de cor */
        if (type == "diffuse")
            this->setDiffuse(color);
        else if (type == "specular")
            this->setSpecular(color);
        else if (type == "ambient")
            this->setAmbient(color);
        else if (type == "emissive")
            this->setEmissive(color);

        /* Caso o tipo de cor não exista */
        else
            throw std::invalid_argument("given color type is not valid");
    }

    /* Definição do shininess do objeto */
    void Primitive::setShininess(float shininess) {

        /* Verifica se a shininess está dentro do intervalo correto */
        if (shininess < 0 || shininess > 128)
            throw std::invalid_argument("given shininess is invalid");

        /* Associação da propriedade */
        this->shininess = shininess;
    }

    /* Definição da textura do objeto */
    void Primitive::setTexture(std::string texture) {
        this->texture = texture::Texture(texture);
    }

    /* Construtor padrão de primitiva */
    Primitive::Primitive() : diffuse(GL_DIFFUSE), ambient(GL_AMBIENT), specular(GL_SPECULAR), emissive(GL_EMISSION), shininess(0), texture() {}

    /* Construtor de cópia de primitiva */
    Primitive::Primitive(const Primitive& primitive) : faces(primitive.faces), diffuse(primitive.diffuse), ambient(primitive.ambient), specular(primitive.specular), emissive(primitive.emissive), shininess(primitive.shininess), texture(primitive.texture) {
        this->buffer[0] = primitive.buffer[0];
        this->buffer[1] = primitive.buffer[1];
    }

    /* Construtor de primitiva através da leitura de ficheiro */
    Primitive::Primitive(std::ifstream& stream) : diffuse(GL_DIFFUSE), ambient(GL_AMBIENT), specular(GL_SPECULAR), emissive(GL_EMISSION), shininess(0), texture() {
        this->read(stream);
    }

    /* Construtor de primitiva através da leitura de ficheiro dado o seu caminho */
    Primitive::Primitive(std::string path) : diffuse(GL_DIFFUSE), ambient(GL_AMBIENT), specular(GL_SPECULAR), emissive(GL_EMISSION), shininess(0), texture() {
        this->read(path);
    }

    /* Construtor de uma primitiva vinda de um ficheiro xml */
    Primitive::Primitive(std::string directory, tinyxml2::XMLElement * model) : diffuse(GL_DIFFUSE), ambient(GL_AMBIENT), specular(GL_SPECULAR), emissive(GL_EMISSION), shininess(0), texture() {
        this->read(directory, model);
    }

    /* Devolução de uma cópia da lista de faces da primitiva */
    std::list<Face> Primitive::getFaces() const {
        return this->faces;
    }

    /* Devolução da cor difusa do objeto */
    lighting::Color Primitive::getDiffuse() const {
        return this->diffuse;
    }

    /* Devolução da cor ambiente do objeto */
    lighting::Color Primitive::getAmbient() const {
        return this->ambient;
    }

    /* Devolução da cor especular do objeto */
    lighting::Color Primitive::getSpecular() const {
        return this->specular;
    }

    /* Devolução da cor emisiva do objeto */
    lighting::Color Primitive::getEmissive() const {
        return this->emissive;
    }

    /* Devolução da shininess do objeto */
    float Primitive::getShininess() const {
        return this->shininess;
    }

    /* Devolução da textura do objeto */
    texture::Texture Primitive::getTexture() const {
        return this->texture;
    }

    /* Rotação de todas as faces de uma primitiva para ficarem viradas para o lado oposto */
    void Primitive::turn() {

        /* Rotação de todas as faces da primitiva */
        for (Face& elem: this->faces)
            elem.turn();
    }

    /* Leitura de uma primitiva vinda de um ficheiro */
    void Primitive::read(std::ifstream& stream) {

        /* Leitura de todas as faces de um ficheiro */
        while (stream.peek() != EOF)
            this->faces.push_back(Face(stream));
    }

    /* Leitura de uma primitiva vinda de um ficheiro */
    void Primitive::read(std::string path) {

        /* Inicialização da stream de leitura */
        std::ifstream stream(path, std::ios::binary);

        /* Verifica se a stream existe e foi aberta */
        if (!(stream.is_open()))
            throw std::invalid_argument("given primitive path is invalid");

        /* Leitura do ficheiro e conversão dos pontos e faces */
        this->read(stream);

        /* Fecho da stream de leitura */
        stream.close();
    }

    /* Leitura de uma primitiva vinda de um ficheiro xml */
    void Primitive::read(std::string directory, tinyxml2::XMLElement * model) {

        /* Verifica se a propriedade de primitiva é válida */
        if (model->ChildElementCount() > 2)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Inicialização da variável que irá armazenar o caminho para o modelo */
        const char * path;

        /* Obtenção do atributo e verificação da existência dele */
        if (model->QueryStringAttribute("file", &path))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Transformação do atributo em string */
        std::string mpath(path);

        /* Leitura do modelo através do ficheiro */
        this->read(directory + path);

        /* Fixa o número de iterações */
        int children = model->ChildElementCount();

        /* Leitura da lista de pontos */
        for (int i = 0; i < children; i++) {

            /* Vai buscar o primeiro elemento */
            tinyxml2::XMLElement * next = model->FirstChildElement();

            /* Armazena o nome do primeiro elemento */
            std::string name = std::string(next->Value());

            /* Verifica qual é o elemento */
            if (name == "color")
                this->readColors(next);
            
            /* Verifica se é uma textura */
            else if (name == "texture")
                this->texture = texture::Texture(directory, next);

            /* Caso o elemento seja inválido */
            else
                throw std::invalid_argument("given xml configuration is invalid");

            /* Apaga o elemento lido */
            model->DeleteChild(next);
        }
    }

    /* Desenho de uma primitiva */
    void Primitive::draw(bool immediate) const {

        /* Aplicação das cores do objeto */
        diffuse.enable();
        ambient.enable();
        specular.enable();
        emissive.enable();

        /* Aplicação da shininess do objeto */
        glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);

        /* Aplica a textura */
        this->texture.load();

        /* Verifica qual o modo de desenho */
        if (immediate) {

            /* Desenho de todos os triângulos presentes na primitiva */
            for (Face elem: this->faces)
                elem.draw();

        } else {

            /* Desenho em modo VBO */
            glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
            glVertexPointer(3, GL_FLOAT, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, this->buffer[1]);
            glNormalPointer(GL_FLOAT, 0, 0);
            glDrawArrays(GL_TRIANGLES, 0, this->faces.size() * 3);

        }
    }

    /* Alimentação de um buffer para desenho em modo VBO */
    void Primitive::feedBuffer() {

        /* Criação do buffers */
        std::vector<float> pointBuffer;
        std::vector<float> normalBuffer;

        /* Alimentação do buffer por parte de todas as faces */
        for (Face face: this->faces) {
            face.feedBufferPoints(pointBuffer);
            face.feedBufferNormals(normalBuffer);
        }

        /* Geração do buffer da primitiva */
        glGenBuffers(2, this->buffer);

        /* Alimentação do buffer para o modo VBO */
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        glBufferData(GL_ARRAY_BUFFER, pointBuffer.size() * sizeof(float), pointBuffer.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[1]);
        glBufferData(GL_ARRAY_BUFFER, normalBuffer.size() * sizeof(float), normalBuffer.data(), GL_STATIC_DRAW);
    }

    /* Operação de comparação por igualdade de primitivas */
    bool Primitive::operator==(const Primitive& primitive) const {

        /* Armazenador de resultado */
        bool result = this->faces.size() == primitive.faces.size();

        /* Verifica a existência do elemento na outra primitiva */
        for (Face elem: this->faces) {
            
            /* Resultado da verificação */
            bool exists = false;

            /* Iterador pela segunda primitiva */
            for (Face sec: primitive.faces)
                if (sec == elem)
                    exists = true;

            /* Atualiza resultado final */ 
            result = result && exists;
        }

        /* Comparação da componente de cores */
        result = result && (this->diffuse == primitive.diffuse) && (this->ambient == primitive.ambient) && (this->specular == primitive.specular) && (this->emissive == primitive.emissive) && (this->shininess == primitive.shininess);

        /* Comparação das texturas */
        result = result && (this->texture == primitive.texture);
            
        /* Devolve a conclusão a que se chegou */
        return result;
    }

    /* Operação de comparação por desigualdade de primitivas */
    bool Primitive::operator!=(const Primitive& primitive) const {

        /* Armazenador de resultado */
        bool result = this->faces.size() == primitive.faces.size();

        /* Verifica a existência do elemento na outra primitiva */
        for (Face elem: this->faces) {
            
            /* Resultado da verificação */
            bool exists = false;

            /* Iterador pela segunda primitiva */
            for (Face sec: primitive.faces)
                if (sec == elem)
                    exists = true;

            /* Atualiza resultado final */ 
            result = result && exists;
        }

        /* Comparação da componente de cores */
        result = result && (this->diffuse == primitive.diffuse) && (this->ambient == primitive.ambient) && (this->specular == primitive.specular) && (this->emissive == primitive.emissive) && (this->shininess == primitive.shininess);

        /* Comparação das texturas */
        result = result && (this->texture == primitive.texture);
            
        /* Devolve a conclusão a que se chegou */
        return !result;
    }

    /* Operação de clonagem de uma primitiva */
    Primitive Primitive::clone() const {
        return Primitive((*this));
    }

    /* Transformação de uma primitiva em formato string */
    std::string Primitive::toString() const {

        /* Criação da string vazia */
        std::string result = "";

        /* Construção da string que irá representar a primitiva */
        for (Face elem: this->faces)
            result += elem.toString();

        /* Colocação da componente de cores */
        result += diffuse.toString() + "\n";
        result += ambient.toString() + "\n";
        result += specular.toString() + "\n";
        result += emissive.toString() + "\n";
        result += std::to_string(this->shininess) + "\n";

        /* Colocação da textura */
        result += "texture: " + this->texture.toString();
        
        /* Devolução da string construída */
        return result;
    }
}