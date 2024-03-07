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

            /* Definição de uma instância global de desenho */
            static World singleton;

            /* Definição das propriedades do mundo */
            projection::Window * window;
            projection::Camera * camera;
            Group * group;

            /* Define a função que será usada para chamar a função de shape da câmera */
            static void shapeCamera(int width, int height);
        
        public:

            /* Construtor padrão de grupo */
            World();

            /* Construtor de cópia de grupo */
            World(const World& world);

            /* Construtor através de um elemento xml */
            World(std::string path, tinyxml2::XMLElement * world);

            /* Construtor através de um elemento xml dado o seu caminho */
            World(std::string path);

            /* Destrutor do objeto mundo */
            ~World();

            /* Definição do mundo como o mundo global */
            void setGlobal() const;

            /* Definição da janela do mundo */
            void setWindow(projection::Window window);

            /* Remoção da janela do mundo */
            void removeWindow();

            /* Devolução do apontador da janela do mundo */
            projection::Window getWindow() const;

            /* Definição da câmera do mundo */
            void setCamera(projection::Camera camera);

            /* Remoção da câmera do mundo */
            void removeCamera();

            /* Devolução do apontador da câmera do mundo */
            projection::Camera getCamera() const;

            /* Definição do grupo do mundo */
            void setGroup(Group group);

            /* Remoção do grupo do mundo */
            void removeGroup();

            /* Devolução do apontador do grupo do mundo */
            Group getGroup() const;

            /* Leitura de um mundo através de um ficheiro xml */
            void read(std::string directory, tinyxml2::XMLElement * world);

            /* Leitura de um mundo através de um ficheiro xml dado o seu caminho */
            void read(std::string path);

            /* Define a função que será usada para dar início à configuração do mundo */
            static void init(int argc, char ** argv, void (*callback)());

            /* Define a função que será usada para dar início ao desenho do mundo em modo imediato */
            static void initDraw();

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