/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/containers/group.hpp"

/* Inclusão de módulos necessários à funcionalidade */
#include "../../inc/transforms/constant/translate.hpp"
#include "../../inc/transforms/constant/rotate.hpp"
#include "../../inc/transforms/constant/scale.hpp"
#include "../../inc/transforms/animated/translate.hpp"
#include "../../inc/transforms/animated/rotate.hpp"
#include <stdexcept>
#include <typeinfo>

/* Inicialização do namespace onde irá ser definida a classe */
namespace containers
{
    /* Leitura de uma primitiva para grupo através de um ficheiro xml */
    void Group::readPrimitive(std::string directory, tinyxml2::XMLElement * model) {

        /* Armazena o nome do elemento */
        std::string name = std::string(model->Value());

        /* Verifica qual é o elemento */
        if (name == "model")
            this->addModel(drawables::Primitive(directory, model));

        /* Caso o elemento seja inválido */
        else
            throw std::invalid_argument("given xml configuration is invalid");
    }

    /* Leitura de uma transformação para grupo através de um ficheiro xml */
    void Group::readTransform(tinyxml2::XMLElement * transform) {

        /* Placeholder para o valor que irá ser usado para verificar se uma translação é animada */
        float time;

        /* Armazena o nome do elemento */
        std::string name = std::string(transform->Value());

        /* Variável que irá armazenar a transformação */
        transforms::Transform * trans = NULL;

        /* Caso a transformação seja uma translação */
        if (name == "translate") {

            /* Verifica se a translação é animada */
            if (!transform->QueryFloatAttribute("time", &time))
                trans = new transforms::animated::Translate(transform);

            /* Caso seja uma translação estática */
            else
                trans = new transforms::constant::Translate(transform);
        }

        /* Caso a transformação seja uma rotação */
        else if (name == "rotate") {

            /* Verifica se a rotação é animada */
            if (!transform->QueryFloatAttribute("time", &time))
                trans = new transforms::animated::Rotate(transform);

            /* Caso seja uma rotação estática */
            else
                trans = new transforms::constant::Rotate(transform);
        }

        /* Caso a transformação seja uma escala */
        else if (name == "scale")
            trans = new transforms::constant::Scale(transform);

        /* Caso o elemento seja inválido */
        else
            throw std::invalid_argument("given xml configuration is invalid");

        /* Adição da transformação lida à lista de transformações */
        this->addTransform(trans);

        /* Remoção da variável temporária */
        delete trans;
    }

    /* Leitura de um sub grupo para grupo através de um ficheiro xml */
    void Group::readGroup(std::string directory, tinyxml2::XMLElement * group) {
        this->addGroup(Group(directory, group));
    }

    /* Construtor padrão de grupo */
    Group::Group() {}

    /* Construtor de cópia de grupo */
    Group::Group(const Group& group) : models(group.models), transforms(group.getTransforms()), groups(group.groups) {}

    /* Construtor através de um elemento xml */
    Group::Group(std::string directory, tinyxml2::XMLElement * group) {
        this->read(directory, group);
    }

    /* Destrutor de um grupo */
    Group::~Group() {

        /* Destroí todos os elementos na lista de transformações */
        for (transforms::Transform * transform: this->transforms)
            delete transform;
    }

    /* Adição de uma primitiva à lista de modelos */
    void Group::addModel(drawables::Primitive model) {
        this->models.push_back(model);
    }

    /* Remoção de uma primitiva à lista de modelos */
    void Group::removeModel(drawables::Primitive model) {
        this->models.remove(model);
    }

    /* Devolução de uma cópia da lista de modelos */
    std::list<drawables::Primitive> Group::getModels() const {
        return this->models;
    }

    /* Adição de uma transformação à lista de transformações */
    void Group::addTransform(transforms::Transform * transform) {

        /* Verifica se já não existe uma transformação do tipo na lista */
        for (transforms::Transform * elem: this->transforms)
            if (typeid(*elem) == typeid(*transform))
                throw std::invalid_argument("given repeated types of transform in same group");

        /* Clonagem da transformação para guardar na lista */
        transforms::Transform * save = transform->clone();

        /* Armazenamento da cópia */
        this->transforms.push_back(save);
    }

    /* Remoção de uma transformação à lista de transformações */
    void Group::removeTransform(transforms::Transform * transform) {
        this->transforms.remove(transform);
    }

    /* Devolução de uma cópia da lista de transformações */
    std::list<transforms::Transform*> Group::getTransforms() const {

        /* Criação de uma lista que será idêntica */
        std::list<transforms::Transform*> transforms;

        /* Adição dos vários elementos à lista */
        for (transforms::Transform * transform: this->transforms) {

            /* Clonagem da transformação */
            transforms::Transform * clone = transform->clone();

            /* Inserção do clone na lista resultado */
            transforms.push_back(clone);
        }

        /* Devolução da lista de clones */
        return transforms;
    }

    /* Adição de um sub grupo à lista de grupos */
    void Group::addGroup(Group group) {
        this->groups.push_back(group);
    }

    /* Remoção de um sub grupo à lista de grupos */
    void Group::removeGroup(Group group) {
        this->groups.remove(group);
    }

    /* Devolução de uma cópia da lista de grupos */
    std::list<Group> Group::getGroups() const {
        return this->groups;
    }

    /* Leitura de um grupo através de um ficheiro xml */
    void Group::read(std::string directory, tinyxml2::XMLElement * group) {

        /* Fixa o número de iterações */
        int children = group->ChildElementCount();
        
        /* Percorre os elementos todos do grupo */
        for (int i = 0; i < children; i++) {

            /* Vai buscar o primeiro elemento */
            tinyxml2::XMLElement * next = group->FirstChildElement();

            /* Armazena o nome do primeiro elemento */
            std::string name = std::string(next->Value());

            /* Verifica qual é o elemento */
            if (name == "models" || name == "transform") {

                /* Fixa o número de iterações */
                int childChildren = next->ChildElementCount();

                /* Percorre os elementos todos da criança */
                for (int i = 0; i < childChildren; i++) {
                    
                    /* Vai buscar o primeiro elemento */
                    tinyxml2::XMLElement * nextChild = next->FirstChildElement();

                    /* Caso a criança esteja num conjunto de modelos */
                    if (name == "models")
                        this->readPrimitive(directory, nextChild);

                    /* Caso a criança esteja num conjunto de transformações */
                    else if (name == "transform")
                        this->readTransform(nextChild);

                    /* Apaga o elemento lido */
                    next->DeleteChild(nextChild);
                }
            }

            /* Caso o elemento seja um sub-grupo */
            else if (name == "group")
                this->readGroup(directory, next);
            
            /* Caso o elemento seja inválido */
            else
                throw std::invalid_argument("given xml configuration is invalid");

            /* Apaga o elemento lido */
            group->DeleteChild(next);
        }
        
    }

    /* Define a função que será usada para desenhar os elementos do grupo */
    void Group::draw(bool immediate) const {

        /* Guarda a matriz de transformações atuais */
        glPushMatrix();

        /* Aplica todas as transformações por ordem */
        for (transforms::Transform * transform: this->transforms)
            transform->apply();

        /* Desenha todas as primitivas uma a uma */
        for (drawables::Primitive model: this->models)
            model.draw(immediate);

        /* Desenha todos os sub-grupos */
        for (Group group: this->groups)
            group.draw(immediate);

        /* Retoma a matriz antes de se ter desenhado o grupo */
        glPopMatrix();
    }

    /* Alimentação dos buffers para desenho em modo VBO */
    void Group::feedBuffer() {
        
        /* Alimentação do buffer de todas as primitivas */
        for (drawables::Primitive& primitive: this->models)
            primitive.feedBuffer();

        /* Alimentação dos buffers dos sub-grupos */
        for (Group& group: this->groups)
            group.feedBuffer();
    }

    /* Define o operador de comparação de igualdade */
    bool Group::operator==(const Group& group) const {

        /* Armazenador de resultado */
        bool result = this->transforms.size() == group.transforms.size();

        /* Verifica a existência da transformação no outro grupo */
        for (transforms::Transform * elem: this->transforms) {
            
            /* Resultado da verificação */
            bool exists = false;

            /* Iterador pelo segundo grupo */
            for (transforms::Transform * sec: group.transforms)
                if ((*sec) == elem)
                    exists = true;

            /* Atualiza resultado final */ 
            result &= exists;
        }

        /* Avalia o tamanho da lista de modelos */
        result = this->models.size() == group.models.size();

        /* Verifica a existência do elemento no outro grupo */
        for (drawables::Primitive elem: this->models) {
            
            /* Resultado da verificação */
            bool exists = false;

            /* Iterador pelo segundo grupo */
            for (drawables::Primitive sec: group.models)
                if (sec == elem)
                    exists = true;

            /* Atualiza resultado final */ 
            result &= exists;
        }

        /* Avalia o tamanho da lista de grupos */
        result = this->groups.size() == group.groups.size();

        /* Verifica a existência do elemento no outro grupo */
        for (Group elem: this->groups) {
            
            /* Resultado da verificação */
            bool exists = false;

            /* Iterador pelo segundo grupo */
            for (Group sec: group.groups)
                if (sec == elem)
                    exists = true;

            /* Atualiza resultado final */ 
            result &= exists;
        }
            
        /* Devolve a conclusão a que se chegou */
        return result;
    }

    /* Define o operador de comparação de desigualdade */
    bool Group::operator!=(const Group& group) const {
        return !(this->operator==(group));
    }

    /* Define a operação de clonagem de um grupo */
    Group Group::clone() const {
        return Group((*this));
    }

    /* Converte o grupo num formato string */
    std::string Group::toString() const {

        /* Inicialização de uma string vazia */
        std::string group = "(GROUP)";

        /* Construção da string com as várias transformações */
        group += "TRANSFORM:\n";

        for (transforms::Transform * transform: this->transforms)
            group += transform->toString() + '\n';

        /* Construção da string com as várias primitivas */
        group += "MODELS:\n";

        for (drawables::Primitive model: this->models)
            group += model.toString();

        /* Construção da string com os vários sub-grupos */
        group += "GROUPS:\n";

        for (Group subgroup: this->groups)
            group += subgroup.toString() + '\n';
        
        /* Devolução da string construída */
        return group;
    }
}
