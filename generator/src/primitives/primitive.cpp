/* Inclusão do cabeçalho da definição de primitiva */
#include "../../inc/primitives/primitive.hpp"

/* Inclusão de livrarias necessárias à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace utilizado para a definição */
namespace primitives
{
    /* Construtor padrão de primitiva */
    Primitive::Primitive() {}

    /* Construtor de cópia de primitiva */
    Primitive::Primitive(const Primitive& primitive) : faces(primitive.faces) {}

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

    /* Devolução de uma cópia da lista de faces da primitiva */
    std::list<Face> Primitive::getFaces() const {
        return this->faces;
    }

    /* Cálculo da normal de todos os pontos por interpolação */
    void Primitive::interpolationNormal() {

        /* Cálculo de todas as normais de todas as faces */
        for (Face &face: this->faces) 
            face.normal();
    }

    /* Cálculo da normal de todos os pontos por Gouraud */
    void Primitive::gouraudNormal() {
        
        /* Criação de um mapa de normais */
        std::unordered_map<std::string, Point> normalMap;

        /* Cálculo das normais de cada ponto */
        for (Face face: this->faces) {

            /* Cálculo da normal */
            face.normal();

            /* Atualização do mapa */
            face.updateNormal(&normalMap);
        }
        
        /* Atualização dos pontos para as respetivas normais */
        for (Face &face: this->faces) 
            face.setNormal(normalMap);
    }

    /* Normalização de todos os pontos de uma primitiva */
    void Primitive::normalize() {

        /* Aplicação da normalização a todas as faces */
        for (Face& elem: this->faces)
            elem.normalize();
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
    void Primitive::rotate(float angle, float rx, float ry, float rz) {

        /* Criação das matrizes de rotação */
        utils::Matrix rotate = utils::Matrix::rotate(angle, rx, ry, rz);

        /* Aplicação da matriz */
        this->transform(rotate);
    }

    /* Escala de uma primitiva dado um vetor de escala */
    void Primitive::scale(float sx, float sy, float sz) {

        /* Criação da matriz de escala */
        utils::Matrix scale = utils::Matrix::scale(sx, sy, sz);

        /* Aplicação da matriz */
        this->transform(scale);
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

    /* Escrita de uma primitiva em ficheiro dado o caminho onde o ficheiro deverá ser guardado */
    void Primitive::write(std::string path) const {

        /* Abertura do ficheiro para escrita binária */
        std::ofstream stream(path, std::ios::binary);

        /* Verifica se foi possível criar o ficheiro */
        if (!stream.is_open())
            std::runtime_error("failed to load or create file");        
        
        /* Escrita do valor dos três pontos em ficheiro */
        this->write(stream);

        /* Fecho do ficheiro aberto */
        stream.close();
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