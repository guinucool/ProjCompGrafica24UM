#ifndef WORLD_HPP
#define WORLD_HPP

#include "../projection/window.hpp"
#include "../projection/camera.hpp"
#include "group.hpp"

/* Inicialização do namespace onde a classe irá ser definida */
namespace containers
{

    /* Definição da classe mundo */
    class World {

        private:

            /* Definição das propriedades do mundo */
            projection::Window * window;
            projection::Camera * camera;
            Group * group;
        
        public:

            /* Construtor padrão de grupo */
            World();

            /* Construtor de cópia de grupo */
            World(const World& world);

            /* Construtor através de um elemento xml */
            World(tinyxml2::XMLElement * group);

            /* Destrutor do objeto mundo */
            ~World();

            /* Definição da janela do mundo */
            void setWindow(projection::Window window);

            /* Remoção da janela do mundo */
            void removeWindow();

            /* Devolução do valor da janela do mundo */
            projection::Window getWindow() const;

            /* Definição da câmera do mundo */
            void setCamera(projection::Camera camera);

            /* Remoção da câmera do mundo */
            void removeCamera();

            /* Devolução do valor da câmera do mundo */
            projection::Camera getCamera() const;

            /* Definição do grupo do mundo */
            void setGroup(Group group);

            /* Remoção do grupo do mundo */
            void removeGroup();

            /* Devolução do valor do grupo do mundo */
            Group getGroup() const;

            /* Leitura de um mundo através de um ficheiro xml */
            void read(tinyxml2::XMLElement * group);

            /* Leitura de um mundo através de um ficheiro xml dado o seu caminho */
            void read(std::string path);

            /* Define a função que será usada para dar início ao desenho do mundo em modo imediato */
            void initDraw() const;

            /* Define o operador de comparação de igualdade */
            bool operator==(const World& world) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const World& world) const;

            /* Define a operação de clonagem de um mundo */
            World clone() const;

            /* Converte o mundo num formato string */
            std::string toString() const;
    };
}

#endif