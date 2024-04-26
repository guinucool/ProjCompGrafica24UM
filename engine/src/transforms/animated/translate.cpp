/* Inclusão do cabeçalho de definição da estrutura de translação */
#include "../../../inc/transforms/animated/translate.hpp"

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inclusão de módulos necessários à funcionalidade */
#include "../../../../shared/inc/geometry/point.hpp"
#include <stdexcept>
#include <typeinfo>
#include <cmath>
#include <iostream>

/* Inicialização do namespace utilizado para a definição */
namespace transforms::animated
{
    /* Definição de propriedades auxiliares ao cálculo da curva */
    std::vector<utils::Matrix> Translate::Y;

    /* Aplicação de uma translação com Catmull-Rom ao cenário */
    void Translate::catmullRom(float t, std::list<geometry::Point*> points) const {

        /* Criação da matriz de Catmull-Rom */
        utils::Matrix M = utils::Matrix::catmullRom();

        /* Criação da matriz de posição e derivada */
        utils::Matrix position(1, 3, 0.0f);
        utils::Matrix derivate(1, 3, 0.0f);

        /* Cálculo das matrizes de aplicação da curva */
        M.curve(t, points, &position, &derivate);

        /* Execução da translação */
        glTranslatef(position[0], position[1], position[2]);

        /* Alinhamento do objeto */
        if (this->isAligned()) {

            /* Cálculo dos vetores de rotação */
            utils::Matrix X = derivate.normalize();
            utils::Matrix Z = derivate.cross(Translate::Y[this->index]).normalize();
            Translate::Y[this->index] = Z.cross(derivate).normalize();

            /* Criação da matriz de rotação */
            utils::Matrix rotate(4);

            /* População da matriz de rotação */
            rotate.at(0, 0) = X[0]; rotate.at(0, 1) = X[1]; rotate.at(0, 2) = X[2];
            rotate.at(1, 0) = Translate::Y[this->index][0]; rotate.at(1, 1) = Translate::Y[this->index][1]; rotate.at(1, 2) = Translate::Y[this->index][2];
            rotate.at(2, 0) = Z[0]; rotate.at(2, 1) = Z[1]; rotate.at(2, 2) = Z[2];
            
            /* Aplicação da matriz de rotação */
            glMultMatrixf(rotate.toArray());
        }
    }

    /* Construtor padrão vazio de translação */
    Translate::Translate() : Transform(), align(true), points(), index(Translate::Y.size()) {

        /* Inicialização das propriedades globais */
        Translate::Y.push_back(utils::Matrix::up());
    }

    /* Construtor parametrizado de translação */
    Translate::Translate(float time, bool align, std::vector<drawables::Point> points) : Transform(time), align(align), points(), index(Translate::Y.size()) {
        
        /* Inicialização das propriedades globais */
        Translate::Y.push_back(utils::Matrix::up());

        /* Adição dos vários pontos à translação */
        for (drawables::Point point : points)
            this->addPoint(point);
    }

    /* Construtor de cópia de translação */
    Translate::Translate(const Translate& translate) : Transform(translate), align(translate.align), points(), index(translate.index) {

        /* Adição dos vários pontos à translação de cópia */
        for (drawables::Point * point : translate.points)
            this->addPoint(*point);
    }

    /* Construtor através de um ficheiro XML de translação */
    Translate::Translate(tinyxml2::XMLElement * transform) : Transform(), index(Translate::Y.size()) {

        /* Inicialização das propriedades globais */
        Translate::Y.push_back(utils::Matrix::up());

        /* Leitura da translação em XML */
        this->read(transform);
    }

    /* Destrutor de translação */
    Translate::~Translate() {

        /* Destroí os pontos na lista de pontos */
        for (drawables::Point * point : this->points)
            delete point;
    }

    /* Adição de um novo ponto à lista de pontos */
    void Translate::addPoint(drawables::Point point) {

        /* Criação do ponto em memória */
        drawables::Point * a_point = new drawables::Point(point);

        /* Associação do apontador à lista de pontos */
        this->points.push_back(a_point);
    }

    /* Devolução da lista de pontos que definem a curva */
    std::vector<drawables::Point> Translate::getPoints() const {

        /* Criação de uma lista resultado */
        std::vector<drawables::Point> result;

        /* População da lista resultado */
        for (drawables::Point * point : this->points)
            result.push_back(*point);

        /* Devolução da lista criada */
        return result;
    }

    /* Devolução do número de pontos que definem a curva*/
    size_t Translate::getSize() const {
        return this->points.size();
    }

    /* Devolução do valor de alinhamento aplicado sobre a animação, alterável */
    bool& Translate::Align() {
        return this->align;
    }

    /* Devolução do valor de alinhamento aplicado sobre a animação */
    const bool& Translate::isAligned() const {
        return this->align;
    }

    /* Devolução do valor do índice usado para o vetor y desta animação, alterável */
    int& Translate::Index() {
        return this->index;
    }

    /* Devolução do valor do índice usado para o vetor y desta animação */
    const int& Translate::getIndex() const {
        return this->index;
    }

    /* Leitura de uma translação através de um ficheiro XML */
    void Translate::read(tinyxml2::XMLElement * transform) {

        /* Verifica se a propriedade de translação é válida */
        if (transform->ChildElementCount() < 4)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Leitura das propriedades do tempo de rotação */
        Transform::read(transform);

        /* Variável que irá armazenar a propriedade de alinhamento */
        bool align;

        /* Leitura e verificação da propriedade de alinhamento */
        if (transform->QueryBoolAttribute("align", &align))
            throw std::invalid_argument("given xml configuration is invalid");

        /* Associação de propriedades */
        this->align = align;

        /* Fixa o número de iterações */
        int children = transform->ChildElementCount();

        /* Leitura da lista de pontos */
        for (int i = 0; i < children; i++) {

            /* Vai buscar o primeiro elemento */
            tinyxml2::XMLElement * next = transform->FirstChildElement();

            /* Armazena o nome do primeiro elemento */
            std::string name = std::string(next->Value());

            /* Verifica qual é o elemento */
            if (name == "point")
                this->addPoint(drawables::Point(next));
            
            /* Caso o elemento seja inválido */
            else
                throw std::invalid_argument("given xml configuration is invalid");

            /* Apaga o elemento lido */
            transform->DeleteChild(next);
        }
    }

    /* Aplicação da translação ao cenário */
    void Translate::apply() const {

        /* Obtenção do número de pontos presentes na curva de Catmull-Rom */
        size_t size = this->getSize();

        /* Cálculo do tempo relativo */
        float rt = this->getRelativeTime() * size;
        int index = floor(rt);
        rt = rt - index;

        /* Criação da lista de pontos para criação da curva */
        std::list<geometry::Point*> curve; 

        /* Cálculo da ordem dos vários pontos da curva */
        index = (index + size - 1) % size;

        /* População da lista de pontos de acordo */
        for (size_t i = 0; i < 4; i++) {

            /* Adição do elemento à lista */
            curve.push_back(this->points[index]);

            /* Passsagem para o índice do próximo ponto */
            index = (index + 1) % size;
        }

        /* Aplicação da curva de Catmull-Rom para o tempo atual */
        this->catmullRom(rt, curve);
    }

    /* Define o operador de comparação de igualdade */
    bool Translate::operator==(const transforms::Transform * transform) const {

        /* Transforma a transformação em translação */
        Translate * translate = (Translate *) transform;

        /* Verificação de igualdade */
        return ((Transform::operator==(transform)) && (translate->align == this->align) && (translate->points == this->points));
    }

    /* Define o operador de comparação de desigualdade */
    bool Translate::operator!=(const transforms::Transform * transform) const {

        /* Transforma a transformação em translação */
        Translate * translate = (Translate *) transform;

        /* Verificação de desigualdade */
        return ((Transform::operator!=(transform)) || (translate->align != this->align) || (translate->points != this->points));
    }

    /* Operação de clonagem de uma translação */
    transforms::Transform * Translate::clone() const {
        return new Translate((*this));
    }

    /* Transformação de uma translação em formato string */
    std::string Translate::toString() const {
        
        /* Criação da string vazia */
        std::string translate = "";

        /* Preenchimento da string resultado */
        translate = "(Translate)" + Transform::toString() + "\naligned: " + std::to_string(this->align) + "\nindex: " + std::to_string(this->index) + "\npoints:\n";

        /* Impressão dos vários pontos que a constituem */
        for (drawables::Point * point: this->points)
            translate += point->toString() + '\n';

        /* Devolução da string construída para resultado */
        return translate;
    }
}