/* Inclusão do cabeçalho da definição de primitiva */
#include "../../inc/drawables/primitive.hpp"

/* Inicialização do namespace utilizado para a definição */
namespace drawables
{
    /* Construtor padrão de primitiva */
    Primitive::Primitive() {}

    /* Construtor de cópia de primitiva */
    Primitive::Primitive(const Primitive& primitive) : faces(primitive.faces) { this->buffer[0] = primitive.buffer[0]; }

    /* Construtor de primitiva através da leitura de ficheiro */
    Primitive::Primitive(std::ifstream& stream) {
        this->read(stream);
    }

    /* Construtor de primitiva através da leitura de ficheiro dado o seu caminho */
    Primitive::Primitive(std::string path) {
        this->read(path);
    }

    /* Construtor de uma primitiva vinda de um ficheiro xml */
    Primitive::Primitive(std::string directory, tinyxml2::XMLElement * model) {
        this->read(directory, model);
    }

    /* Devolução de uma cópia da lista de faces da primitiva */
    std::list<Face> Primitive::getFaces() const {
        return this->faces;
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

        /* Verifica se a propriedade de janela é válida */
        if (model->ChildElementCount() != 0)
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
    }

    /* Desenho de uma primitiva */
    void Primitive::draw(bool immediate) const {

        /* Verifica qual o modo de desenho */
        if (immediate) {

            /* Desenho de todos os triângulos presentes na primitiva */
            for (Face elem: this->faces)
                elem.draw();

        } else {

            /* Desenho em modo VBO */
            glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
            glVertexPointer(3, GL_FLOAT, 0, 0);
            glDrawArrays(GL_TRIANGLES, 0, this->faces.size() * 3);

        }
    }

    /* Alimentação de um buffer para desenho em modo VBO */
    void Primitive::feedBuffer() {

        /* Criação do buffer de vértices */
        std::vector<float> buffer;

        /* Alimentação do buffer por parte de todas as faces */
        for (Face face: this->faces)
            face.feedBuffer(buffer);

        /* Geração do buffer da primitiva */
        glGenBuffers(1, this->buffer);

        /* Alimentação do buffer para o modo VBO */
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);
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
            result &= exists;
        }
            
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
            result &= exists;
        }
            
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
        
        /* Devolução da string construída */
        return result;
    }
}