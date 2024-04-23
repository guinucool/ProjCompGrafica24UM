/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/containers/world.hpp"

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inclusão de módulos necessários à funcionalidade */
#include "../../../shared/inc/exception/unvalues.hpp"
#include <stdexcept>

/* Inicialização do namespace onde irá ser definida a classe */
namespace containers
{
    /* Definição de uma instância global de desenho */
    World World::singleton;

    /* Define a função que será usada para chamar a função de shape da câmera */
    void World::shapeCamera(int width, int height) {
        World::singleton.camera->shapeCamera(width, height);
    }

    /* Construtor padrão de grupo */
    World::World() : window(NULL), camera(NULL), group(NULL) {}

    /* Construtor de cópia de grupo */
    World::World(const World& world) {
        this->setWindow(*(world.window));
        this->setCamera(*(world.camera));
        this->setGroup(*(world.group));
    }

    /* Construtor através de um elemento xml */
    World::World(std::string directory, tinyxml2::XMLElement * world) : window(NULL), camera(NULL), group(NULL) {
        this->read(directory, world);
    }

    /* Construtor através de um elemento xml dado o seu caminho */
    World::World(std::string path) : window(NULL), camera(NULL), group(NULL) {
        this->read(path);
    }

    /* Destrutor do objeto mundo */
    World::~World() {
        this->removeWindow();
        this->removeCamera();
        this->removeGroup();
    }

    /* Definição do mundo como o mundo global */
    void World::setGlobal() const {

        /* Definição das propriedades do singleton */
        World::singleton.setWindow(*(this->window));
        World::singleton.setCamera(*(this->camera));
        World::singleton.setGroup(*(this->group));
    }

    /* Definição da janela do mundo */
    void World::setWindow(projection::Window window) {
        this->removeWindow();
        this->window = new projection::Window(window);
    }

    /* Remoção da janela do mundo */
    void World::removeWindow() {

        /* Caso exista, remove a janela do mundo */
        if (this->window)
            delete this->window;
    }

    /* Devolução do valor da janela do mundo */
    projection::Window World::getWindow() const {
        return *(this->window);
    }

    /* Definição da câmera do mundo */
    void World::setCamera(projection::Camera camera) {
        this->removeCamera();
        this->camera = new projection::Camera(camera);
    }

    /* Remoção da câmera do mundo */
    void World::removeCamera() {

        /* Caso exista, remove a câmera do mundo */
        if (this->camera)
            delete this->camera;
    }

    /* Devolução do valor da câmera do mundo */
    projection::Camera World::getCamera() const {
        return *(this->camera);
    }

    /* Definição do grupo do mundo */
    void World::setGroup(Group group) {
        this->removeGroup();
        this->group = new Group(group);
    }

    /* Remoção do grupo do mundo */
    void World::removeGroup() {

        /* Caso exista, remove o grupo do mundo */
        if (this->group)
            delete this->group;
    }

    /* Devolução do valor do grupo do mundo */
    Group World::getGroup() const {
        return *(this->group);
    }

    /* Leitura de um mundo através de um ficheiro xml */
    void World::read(std::string directory, tinyxml2::XMLElement * world) {

        /* Fixa o número de iterações */
        int children = world->ChildElementCount();

        /* Percorre todos os elementos presentes no mundo */
        for (int i = 0; i < children; i++)
        {
            /* Lê o próximo elemento na árvore */
            tinyxml2::XMLElement * next = world->FirstChildElement();

            /* Armazena o nome do elemento */
            std::string name = std::string(next->Value());

            /* Verifica qual é o elemento e transforma-o num tipo */
            if (name == "window" && !(this->window))
                this->setWindow(projection::Window(next));
            
            else if (name == "camera" && !(this->camera))
                this->setCamera(projection::Camera(next));

            else if (name == "group" && !(this->group))
                this->setGroup(Group(directory, next));

            /* No caso de ser um elemento inválido ou repetido */
            else
                throw std::invalid_argument("given xml configuration is invalid");

            /* Apaga o elemento lido */
            world->DeleteChild(next);
        }
        
        /* Verifica se existe algum elemento essencial em falta */
        if (!(this->window) || !(this->camera) || !(this->group))
            throw std::invalid_argument("given xml configuration is invalid");
    }

    /* Leitura de um mundo através de um ficheiro xml dado o seu caminho */
    void World::read(std::string path) {

        /* Criação do documento xml */
        tinyxml2::XMLDocument doc;

        /* Abertura do documento xml */
        if (doc.LoadFile(path.c_str()))
            throw std::invalid_argument("given xml configuration file path is invalid");

        /* Verificação do número de elementos na base do ficheiro */
        if (doc.ChildElementCount() != 1)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Armazenador do elemento mundo */
        tinyxml2::XMLElement * world;

        /* Verificação da existência de um primeiro elemento mundo */
        if ((world = doc.FirstChildElement("world")) == 0)
            throw std::invalid_argument("given xml configuration is invalid");

        /* Criação do caminho de origem do ficheiro xml */
        size_t lastSlashPos = path.find_last_of("/\\");
        std::string directory = "";

        /* Verifica se existe última barra */
        if (lastSlashPos != std::string::npos)
            directory = path.substr(0, lastSlashPos + 1);

        /* Leitura do xml */
        this->read(directory, world);

        /* Destruição da árvore */
        doc.DeleteChild(world);
    }

    /* Define a função que será usada para dar início à configuração do mundo */
    void World::init(int argc, char ** argv, void (*callback)()) {

        /* Inicialização do OpenGL */
        glutInit(&argc, argv);
	    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

        /* Verifica a existência de uma janela */
        if (!(World::singleton.window))
            throw customException::undefined_value("window property is not defined properly");

        /* Verifica a existência de uma câmera */
        if (!(World::singleton.camera))
            throw customException::undefined_value("camera property is not defined properly");

        /* Inicialização da janela */
        World::singleton.window->defineWindow();

        /* Definição das funções de representação */
        glutReshapeFunc(World::shapeCamera);
        glutDisplayFunc(callback);
        glutIdleFunc(callback);

        /* Configurações do OpenGL */
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        /* Inicialização do GLUT */
        glutMainLoop();
    }

    /* Define a função que será usada para dar início ao desenho do mundo em modo imediato */
    void World::initDraw() {

        /* Verifica a existência de uma câmera */
        if (!(World::singleton.camera))
            throw customException::undefined_value("camera property is not defined properly");

        /* Verifica a existência de um grupo */
        if (!(World::singleton.group))
            throw customException::undefined_value("main group property is not defined properly");

        /* Limpeza dos buffers */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    glPolygonMode( GL_FRONT, GL_LINE );

        /* Inicialização da matriz identidade */
        glLoadIdentity();

        /* Desenha a câmera */
        World::singleton.camera->defineCamera();

        /* Desenha o grupo */
        World::singleton.group->draw();

        /* Troca de buffers para desenhar no ecrã */
        glutSwapBuffers();
    }

    /* Define o operador de comparação de igualdade */
    bool World::operator==(const World& world) const {
        return *(this->group) == *(world.group) && *(this->camera) == *(world.camera) && *(this->window) == *(world.window);
    }

    /* Define o operador de comparação de desigualdade */
    bool World::operator!=(const World& world) const {
        return *(this->group) != *(world.group) || *(this->camera) != *(world.camera) || *(this->window) != *(world.window);
    }

    /* Define a operação de clonagem de um mundo */
    World World::clone() const {
        return World((*this));
    }

    /* Converte o mundo num formato string */
    std::string World::toString() const {

        /* Inicialização de uma string vazia */
        std::string world = "";

        /* Informação da janela */
        world += "Window: ";

        /* Verifica a existência de uma janela */
        if(this->window)
            world += this->window->toString();
        else
            world += "NULL";

        /* Criação de uma nova linha */
        world += '\n';

        /* Informação da câmera */
        world += "Camera: \n";

        /* Verifica a existência de uma câmera */
        if(this->camera)
            world += this->camera->toString();
        else
            world += "NULL";

        /* Informação do grupo */
        world += "Group: \n";

        /* Verifica a existência de um grupo */
        if(this->group)
            world += this->group->toString();
        else
            world += "NULL";

        /* Devolução da string construída */
        return world;
    }
}
