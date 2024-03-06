/* Inclusão do cabeçalho da definição de primitiva */
#include "../../inc/drawables/primitive.hpp"

/* Inicialização do namespace utilizado para a definição */
namespace drawables
{
    /* Construtor padrão de primitiva */
    Primitive::Primitive() {}

    /* Construtor de cópia de primitiva */
    Primitive::Primitive(const Primitive& primitive) : faces(primitive.faces) {}

    /* Construtor de primitiva através da leitura de ficheiro */
    Primitive::Primitive(std::ifstream& stream) {
        this->read(stream);
    }

    /* Construtor de primitiva através da leitura de ficheiro dado o seu caminho */
    Primitive::Primitive(std::string path) {
        this->read(path);
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
        while (!(stream.eof()))
            this->faces.push_back(Face(stream));
    }

    /* Leitura de uma primitiva vinda de um ficheiro */
    void Primitive::read(std::string path) {

        /* Inicialização da stream de leitura */
        std::ifstream stream(path, std::ios::binary);

        /* Leitura do ficheiro e conversão dos pontos e faces */
        this->read(stream);

        /* Fecho da stream de leitura */
        stream.close();
    }

    /* Desenho de uma primitiva no modo imediato */
    void Primitive::draw() const {

        /* Desenho de todos os triângulos presentes na primitiva */
        for (Face elem: this->faces)
            elem.draw();
    }

    /* Alimentação de um buffer para desenho em modo VBO */
    void Primitive::feedBuffer(std::vector<float>& buffer) const {

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