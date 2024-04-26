#ifndef GROUP_HPP
#define GROUP_HPP

#include "../../../external/tinyxml2/tinyxml2.h"
#include "../drawables/primitive.hpp"
#include "../transforms/transform.hpp"

/* Inicialização do namespace onde a classe irá ser definida */
namespace containers
{

    /* Definição da classe grupo */
    class Group {

        private:

            /* Leitura de uma primitiva para grupo através de um ficheiro xml */
            void readPrimitive(std::string directory, tinyxml2::XMLElement * model);

            /* Leitura de uma transformação para grupo através de um ficheiro xml */
            void readTransform(tinyxml2::XMLElement * transform);

            /* Leitura de um sub grupo para grupo através de um ficheiro xml */
            void readGroup(std::string directory, tinyxml2::XMLElement * group);

            /* Definição das propriedades do grupo */
            std::list<drawables::Primitive> models;
            std::list<transforms::Transform*> transforms;
            std::list<Group> groups;
        
        public:

            /* Construtor padrão de grupo */
            Group();

            /* Construtor de cópia de grupo */
            Group(const Group& group);

            /* Construtor através de um elemento xml */
            Group(std::string directory, tinyxml2::XMLElement * group);

            /* Destrutor de um grupo */
            ~Group();

            /* Adição de uma primitiva à lista de modelos */
            void addModel(drawables::Primitive model);

            /* Remoção de uma primitiva à lista de modelos */
            void removeModel(drawables::Primitive model);

            /* Devolução de uma cópia da lista de modelos */
            std::list<drawables::Primitive> getModels() const;

            /* Adição de uma transformação à lista de transformações */
            void addTransform(transforms::Transform * transform);

            /* Remoção de uma transformação à lista de transformações */
            void removeTransform(transforms::Transform * transform);

            /* Devolução de uma cópia da lista de transformações */
            std::list<transforms::Transform*> getTransforms() const;

            /* Adição de um sub grupo à lista de grupos */
            void addGroup(Group group);

            /* Remoção de um sub grupo à lista de grupos */
            void removeGroup(Group group);

            /* Devolução de uma cópia da lista de grupos */
            std::list<Group> getGroups() const;

            /* Leitura de um grupo através de um ficheiro xml */
            void read(std::string directory, tinyxml2::XMLElement * group);

            /* Define a função que será usada para desenhar os elementos do grupo */
            void draw(bool immediate) const;

            /* Alimentação dos buffers para desenho em modo VBO */
            void feedBuffer();

            /* Define o operador de comparação de igualdade */
            bool operator==(const Group& group) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const Group& group) const;

            /* Define a operação de clonagem de um grupo */
            Group clone() const;

            /* Converte o grupo num formato string */
            std::string toString() const;
    };
}

#endif