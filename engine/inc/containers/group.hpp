#ifndef GROUP_HPP
#define GROUP_HPP

#include "../../../external/tinyxml2/tinyxml2.h"
#include "../drawables/primitive.hpp"

/* Inicialização do namespace onde a classe irá ser definida */
namespace containers
{

    /* Definição da classe grupo */
    class Group {

        private:

            /* Definição das propriedades do grupo */
            std::list<drawables::Primitive> models;
        
        public:

            /* Construtor padrão de grupo */
            Group();

            /* Construtor de cópia de grupo */
            Group(const Group& group);

            /* Construtor através de um elemento xml */
            Group(tinyxml2::XMLElement * group);

            /* Adição de uma primitiva à lista de modelos */
            void addModel(drawables::Primitive model);

            /* Remoção de uma primitiva à lista de modelos */
            void removeModel(drawables::Primitive model);

            /* Devolução de uma cópia da lista de modelos */
            std::list<drawables::Primitive> getModels() const;

            /* Leitura de um grupo através de um ficheiro xml */
            void read(tinyxml2::XMLElement * group);

            /* Define a função que será usada para desenhar os elementos do grupo em modo imediato */
            void draw() const;

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