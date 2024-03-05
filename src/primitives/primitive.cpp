/* Inclusão do cabeçalho da definição de primitiva */
#include "../../includes/primitives/primitive.hpp"

/* Inicialização do namespace utilizado para a definição */
namespace primitives
{
    /* Construtor padrão de primitiva */
    Primitive::Primitive() {}

    /* Construtor de cópia de primitiva */
    Primitive::Primitive(const Primitive& primitive) : faces(primitive.faces) {}

    /* Construtor por leitura de ficheiro de primitiva */
    Primitive::Primitive(std::ifstream& stream) {
        this->read(stream);
    }

    /* Adicionar uma primitiva */
    void Primitive::add(Primitive primitive) {
        this->faces.insert(this->faces.end(), primitive.faces.begin(), primitive.faces.end());
    }

    /* Adicionar uma face */
    void Primitive::add(Face face) {
        this->faces.push_back(face);
    }

    /* Adicionar um triângulo */
    void Primitive::addTriangle(Point first, Point second, Point third) {
        this->faces.push_back(Face(first, second, third));
    }

    /* Adicionar um quadrado */
    void Primitive::addSquare(Point first, Point second, Point third, Point forth) {
        this->faces.push_back(Face(first, second, third));
        this->faces.push_back(Face(third, forth, first));
    }

    /* Transformação de uma primitiva dada uma matriz */
    void Primitive::transform(const utils::Matrix& transform) {

        /* Aplicação da matriz a todas as faces */
        for (Face& elem: this->faces)
            elem.transform(transform);
    }

    /* Translação de uma primitiva dado um vetor */
    void Primitive::translateD(float dx, float dy, float dz) {

        /* Criação da matriz de translação */
        utils::Matrix translate = utils::Matrix::translateD(dx, dy, dz);

        /* Aplicação da matriz */
        this->transform(translate);
    }

    /* Translação de uma primitiva dado um vetor polar */
    void Primitive::translateP(float radius, float alpha, float beta) {

        /* Criação da matriz de translação */
        utils::Matrix translate = utils::Matrix::translateP(radius, alpha, beta);

        /* Aplicação da matriz */
        this->transform(translate);
    }

    /* Rotação de uma primitiva dado o ângulo de rotação sobre cada eixo */
    void Primitive::rotate(float ax, float ay, float az) {

        /* Criação das matrizes de rotação */
        utils::Matrix rotateX = utils::Matrix::rotateX(ax);
        utils::Matrix rotateY = utils::Matrix::rotateY(ay);
        utils::Matrix rotateZ = utils::Matrix::rotateZ(az);

        /* Aplicação da matriz */
        this->transform(rotateX * rotateY * rotateZ);
    }

    /* Rotação de todas as faces de uma primitiva para ficarem viradas para o lado oposto */
    void Primitive::turn() {

        /* Rotação de todas as faces da primitiva */
        for (Face& elem: this->faces)
            elem.turn();
    }

    /* Escrita de uma primitiva em ficheiro */
    void Primitive::write(std::ofstream& stream) const {

        /* Escrita de todas as faces em ficheiro */
        for (Face elem: this->faces)
            elem.write(stream);
    }

    /* Leitura de uma primitiva vinda de um ficheiro */
    void Primitive::read(std::ifstream& stream) {

        /* Leitura de todas as faces de um ficheiro */
        while (!(stream.eof()))
            this->faces.push_back(Face(stream));
    }

    /* Desenho de uma primitiva no modo imediato */
    void Primitive::draw() const {

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
            result += elem.toString() + '\n';
        
        /* Devolução da string construída */
        return result;
    }
}