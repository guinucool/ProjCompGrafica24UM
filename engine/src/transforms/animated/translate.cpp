/* Inclusão do cabeçalho de definição da estrutura de translação */
#include "../../../inc/transforms/animated/translate.hpp"

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>
#include <typeinfo>
#include <cmath>

/* Inicialização do namespace utilizado para a definição */
namespace transforms::animated
{
    /* Definição de propriedades auxiliares ao cálculo da curva */
    std::vector<utils::Matrix> Translate::Y;

    /* Aplicação da translação de Catmull-Rom */
    void Translate::catmullRomPath(float t, utils::Matrix M) const {

        /* Criação da matriz de tempo */
        utils::Matrix T(1, 4, 0.0f);

        /* Cálculo da matriz temporal */
        T[0] = pow(t, 3);
        T[1] = pow(t, 2);
        T[2] = pow(t, 1);
        T[3] = 1;

        /* Cálculo do vetor de translação */
        utils::Matrix P = T * M;

        /* Execução da translação */
        glTranslatef(P[0], P[1], P[2]);
    }

    /* Aplicação da rotação de Catmull-Rom */
    void Translate::catmullRomAlign(float t, utils::Matrix M) const {

        /* Cálculo da matriz de tempo derivada */
        utils::Matrix T(1, 4, 0.0f);

        /* Cálculo da matriz temporal */
        T[0] = 3 * pow(t, 2);
        T[1] = 2 * t;
        T[2] = 1;
        T[3] = 0;

        /* Cálculo dos vetores de rotação */
        utils::Matrix D = (T * M).normalize();
        utils::Matrix zrot = D.cross(Translate::Y[this->index]).normalize();
        Translate::Y[this->index] = zrot.cross(D).normalize();

        /* Criação da matriz de rotação */
        utils::Matrix rotate(4);

        /* População da matriz de rotação */
        rotate.at(0, 0) = D[0]; rotate.at(0, 1) = D[1]; rotate.at(0, 2) = D[2];
        rotate.at(1, 0) = Translate::Y[this->index][0]; rotate.at(1, 1) = Translate::Y[this->index][1]; rotate.at(1, 2) = Translate::Y[this->index][2];
        rotate.at(2, 0) = zrot[0]; rotate.at(2, 1) = zrot[1]; rotate.at(2, 2) = zrot[2];
        
        /* Aplicação da matriz de rotação */
        glMultMatrixf(rotate.toArray());
    }

    /* Aplicação de uma translação com Catmull-Rom ao cenário */
    void Translate::catmullRom(float t) const {

        /* Obtenção do número de pontos presentes na curva de Catmull-Rom */
        size_t size = this->getSize();

        /* Cálculo do tempo relativo */
        float rt = t * size;

        /* Cálculo do segmento atual */
        int index = floor(rt);

        /* Cálculo do tempo relativo ao segmento atual */
        rt = rt - index;

        /* Cálculo do índice inicial da matriz */
        index = (index + size - 1) % size;

        /* Criação da matriz de Catmull-Rom */
        utils::Matrix M = utils::Matrix::catmullRom();

        /* Criação da matriz de pontos */
        utils::Matrix P(4, 3, 0.0f);

        /* População da matriz de pontos de acordo */
        for (size_t i = 0; i < 4; i++) {

            /* Associação das coordenadas do ponto à matriz */
            P.at(i, 0) = this->points[index].X();
            P.at(i, 1) = this->points[index].Y();
            P.at(i, 2) = this->points[index].Z();

            /* Passsagem para o índice do próximo ponto */
            index = (index + 1) % size;
        }
        
        /* Multiplicação das matrizes */
        utils::Matrix A = M * P;

        /* Aplicação da curva de Catmull-Rom */
        this->catmullRomPath(rt, A);

        /* Verifica se é pretendido o alinhamento do objeto */
        if (this->isAligned())
            this->catmullRomAlign(rt, A);
    }

    /* Construtor padrão vazio de translação */
    Translate::Translate() : Transform(), align(true), points(), index(Translate::Y.size()) { Translate::Y.push_back(utils::Matrix::up()); }

    /* Construtor parametrizado de translação */
    Translate::Translate(float time, bool align, std::vector<drawables::Point> points) : Transform(time), align(align), points(points), index(Translate::Y.size()) { Translate::Y.push_back(utils::Matrix::up()); }

    /* Construtor de cópia de translação */
    Translate::Translate(const Translate& translate) : Transform(translate), align(translate.align), points(translate.points), index(Translate::Y.size()) { Translate::Y.push_back(utils::Matrix::up()); }

    /* Construtor através de um ficheiro XML de translação */
    Translate::Translate(tinyxml2::XMLElement * transform) : Transform(), index(Translate::Y.size()) {

        /* Criação do vetor direcional em y inicial */
        Translate::Y.push_back(utils::Matrix::up());

        /* Leitura da translação em XML */
        this->read(transform);
    }

    /* Adição de um novo ponto à lista de pontos */
    void Translate::addPoint(drawables::Point point) {
        this->points.push_back(point);
    }

    /* Devolução do valor da transformação aplicada sobre o eixo y */
    std::vector<drawables::Point> Translate::getPoints() const {
        return this->points;
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

        /* Cálculo do tempo do estado atual da animação */
        float t = this->getRelativeTime();

        /* Aplicação da curva de Catmull-Rom para o tempo atual */
        this->catmullRom(t);
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
        for (drawables::Point point: this->points)
            translate += point.toString() + '\n';

        /* Devolução da string construída para resultado */
        return translate;
    }
}