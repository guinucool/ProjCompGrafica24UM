/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/containers/group.hpp"

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>

/* Inicialização do namespace onde irá ser definida a classe */
namespace containers
{
    /* Construtor padrão de grupo */
    Group::Group() {}

    /* Construtor de cópia de grupo */
    Group::Group(const Group& group) : models(group.models) {}

    /* Construtor através de um elemento xml */
    Group::Group(std::string directory, tinyxml2::XMLElement * group) {
        this->read(directory, group);
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

    /* Leitura de um grupo através de um ficheiro xml */
    void Group::read(std::string directory, tinyxml2::XMLElement * group) {
        
        /* Percorre os elementos todos do grupo */
        for (int i = 0; i < group->ChildElementCount(); i++) {

            /* Vai buscar o primeiro elemento */
            tinyxml2::XMLElement * next = group->FirstChildElement();

            /* Armazena o nome do primeiro elemento */
            const char * name = next->Value();

            /* Verifica qual é o elemento */
            if (name == "models") {

                /* Percorre os elementos todos dos modelos */
                for (int i = 0; i < next->ChildElementCount(); i++) {
                    
                    /* Vai buscar o primeiro elemento */
                    tinyxml2::XMLElement * nextModels = next->FirstChildElement();

                    /* Armazena o nome do primeiro elemento */
                    const char * nameModels = nextModels->Value();

                    /* Verifica qual é o elemento */
                    if (nameModels == "model")
                        this->addModel(drawables::Primitive(directory, nextModels));

                    /* Caso o elemento seja inválido */
                    else
                        throw std::invalid_argument("given xml configuration is invalid");

                    /* Apaga o elemento lido */
                    next->DeleteChild(nextModels);
                    delete nameModels;
                }
            }
            
            /* Caso o elemento seja inválido */
            else
                throw std::invalid_argument("given xml configuration is invalid");

            /* Apaga o elemento lido */
            group->DeleteChild(next);
            delete name;
        }
        
    }

    /* Define a função que será usada para desenhar os elementos do grupo em modo imediato */
    void Group::draw() const {

        /* Desenha todas as primitivas uma a uma */
        for (drawables::Primitive model: this->models)
            model.draw();
    }

    /* Define o operador de comparação de igualdade */
    bool Group::operator==(const Group& group) const {

        /* Armazenador de resultado */
        bool result = this->models.size() == group.models.size();

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
            
        /* Devolve a conclusão a que se chegou */
        return result;
    }

    /* Define o operador de comparação de desigualdade */
    bool Group::operator!=(const Group& group) const {

        /* Armazenador de resultado */
        bool result = this->models.size() == group.models.size();

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
            
        /* Devolve a conclusão a que se chegou */
        return !result;
    }

    /* Define a operação de clonagem de um grupo */
    Group Group::clone() const {
        return Group((*this));
    }

    /* Converte o grupo num formato string */
    std::string Group::toString() const {

        /* Inicialização de uma string vazia */
        std::string group = "";

        /* Construção da string com as várias primitivas */
        group += "MODELS:\n";

        for (drawables::Primitive model: this->models)
            group += model.toString();
        
        /* Devolução da string construída */
        return group;
    }
}
