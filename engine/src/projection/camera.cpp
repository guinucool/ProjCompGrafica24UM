/* Inclusão do cabeçalho de definição da classe */
#include "../../inc/projection/camera.hpp"

/* Inclusão do OpenGL e do GLUT */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Inclusão de módulos necessários à funcionalidade */
#include <stdexcept>
#include <limits>

/* Inicialização do namespace onde irá ser definida a classe */
namespace projection
{
    /* Construtor padrão de câmera */
    Camera::Camera() : origin(), lookAt(), up(0, 1, 0), fov(60), near(1), far(1000) {}

    /* Construtor parametrizado de câmera */
    Camera::Camera(drawables::Point origin, drawables::Point lookAt, drawables::Point up, float fov, float near, float far) : origin(origin), lookAt(lookAt), up(up), far(std::numeric_limits<float>::max()) {
        this->setFov(fov);
        this->setNear(near);
        this->setFar(far);
    }

    /* Construtor de cópia de câmera */
    Camera::Camera(const Camera& camera) : origin(camera.origin), lookAt(camera.lookAt), up(camera.up), fov(camera.fov), near(camera.near), far(camera.far) {}

    /* Construtor através de um elemento xml */
    Camera::Camera(tinyxml2::XMLElement * camera) : origin(), lookAt(), up(0, 1, 0), fov(60), near(1), far(1000) {
        this->read(camera);
    }

    /* Devolução da referência do ponto de origem */
    drawables::Point& Camera::Origin() {
        return this->origin;
    }

    /* Devolução da referência do ponto de origem sem possibilidade de alteração */
    const drawables::Point& Camera::Origin() const {
        return this->origin;
    }

    /* Devolução da referência do ponto de vigia */
    drawables::Point& Camera::LookAt() {
        return this->lookAt;
    }

    /* Devolução da referência do ponto de vigia sem possibilidade de alteração */
    const drawables::Point& Camera::LookAt() const {
        return this->lookAt;
    }

    /* Devolução da referência do "ponto" up */
    drawables::Point& Camera::Up() {
        return this->up;
    }

    /* Devolução da referência do "ponto" up sem possibilidade de alteração */
    const drawables::Point& Camera::Up() const {
        return this->up;
    }

    /* Definição do valor do fov */
    void Camera::setFov(float fov) {

        /* Verifica se o fov fornecido é válido */
        if (fov < 0 || fov > 180)
            throw std::invalid_argument("given fov is invalid");
        
        /* Define o fov */
        this->fov = fov;
    }

    /* Devolução do valor do fov */
    float Camera::getFov() const {
        return this->fov;
    }

    /* Definição do valor do near */
    void Camera::setNear(float near) {

        /* Verifica se o near fornecido é válido */
        if (near <= 0 || near >= this->far)
            throw std::invalid_argument("given near is invalid");
        
        /* Define o fov */
        this->near = near;
    }

    /* Devolução do valor do near */
    float Camera::getNear() const {
        return this->near;
    }

    /* Definição do valor do far */
    void Camera::setFar(float far) {
        
        /* Verifica se o far fornecido é válido */
        if (far <= 0 || far <= near)
            throw std::invalid_argument("given far is invalid");

        /* Define o far */
        this->far = far;
    }

    /* Devolução do valor do far */
    float Camera::getFar() const {
        return this->far;
    }

    /* Leitura de uma câmera através de um ficheiro xml */
    void Camera::read(tinyxml2::XMLElement * camera) {

        /* Fixa o número de iterações */
        int children = camera->ChildElementCount();
        
        /* Percorre os elementos todos */
        for (int i = 0; i < children; i++) {

            /* Vai buscar o primeiro elemento */
            tinyxml2::XMLElement * next = camera->FirstChildElement();

            /* Armazena o nome do primeiro elemento */
            std::string name = std::string(next->Value());

            /* Verifica qual é o primeiro elemento */
            if (name == "position" || name == "lookAt" || name == "up") {
                
                /* Inicialização de variáveis para armazenar as coordenadas */
                float x, y, z;

                /* Obtenção dos atributos e verificação da existência deles */
                if (next->QueryFloatAttribute("x", &x) || next->QueryFloatAttribute("y", &y) || next->QueryFloatAttribute("z", &z))
                    throw std::invalid_argument("given xml configuration is invalid");

                /* Associação das propriedades */
                if (name == "position")
                    this->origin.setCoords(x, y, z);
                else if (name == "lookAt")
                    this->lookAt.setCoords(x, y, z);
                else
                    this->up.setCoords(x, y, z);
            }
            
            else if (name == "projection") {

                /* Inicialização de variáveis para armazenar as propriedades */
                float fov = this->fov, near = this->near, far = this->far;

                /* Obtenção dos atributos e verificação da existência deles */
                bool vFov = next->QueryFloatAttribute("fov", &fov);
                bool vNear = next->QueryFloatAttribute("near", &near);
                bool vFar = next->QueryFloatAttribute("far", &far);

                /* Obtenção dos atributos e verificação da existência deles */
                if (vFov && vNear && vFar)
                    throw std::invalid_argument("given xml configuration is invalid");

                /* Associação das propriedades */
                this->setFov(fov);
                this->setNear(near);
                this->setFar(far);
            }

            /* Caso seja inválido */
            else
                throw std::invalid_argument("given xml configuration is invalid");

            /* Apaga o elemento lido */
            camera->DeleteChild(next);
        }
    }

    /* Define a câmera que vai ser usada no cenário */
    void Camera::defineCamera() const {
        gluLookAt(this->origin.X(), this->origin.Y(), this->origin.Z(), this->lookAt.X(), this->lookAt.Y(), this->lookAt.Z(), this->up.X(), this->up.Y(), this->up.Z());
    }

    /* Define a função que será usada para definir o tamanho da câmera */
    void Camera::shapeCamera(int width, int height) const {

        /* Prevenção de janelas inexistentes */
        if (height == 0)
		    height = 1;

        /* Cálculo do ratio */
        float ratio = width * 1.0f / height;

        /* Entrar no modo de projeção para definir a perspetiva da câmera */
        glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();

        /* Definição do viewport da janela */
	    glViewport(0, 0, width, height);

        /* Definição da perspetiva da câmera */
	    gluPerspective(this->fov, ratio, this->near, this->far);
	
        /* Retomar o modo de modelos */
	    glMatrixMode(GL_MODELVIEW);
    }

    /* Define o operador de comparação de igualdade */
    bool Camera::operator==(const Camera& camera) const {
        return this->origin == camera.origin
               && this->lookAt == camera.lookAt
               && this->up == camera.up
               && this->fov == camera.fov
               && this->near == camera.near
               && this->far == camera.far;
    }

    /* Define o operador de comparação de desigualdade */
    bool Camera::operator!=(const Camera& camera) const {
        return this->origin != camera.origin
               || this->lookAt != camera.lookAt
               || this->up != camera.up
               || this->fov != camera.fov
               || this->near != camera.near
               || this->far != camera.far;
    }

    /* Define a operação de clonagem de uma câmera */
    Camera Camera::clone() const {
        return Camera((*this));
    }

    /* Converte a câmera num formato string */
    std::string Camera::toString() const {

        /* Inicialização de uma string vazia */
        std::string camera = "";

        /* Construção da string */
        camera += "Origin-" + this->origin.toString() + '\n';
        camera += "LookAt-" + this->lookAt.toString() + '\n';
        camera += "Up-" + this->up.toString() + '\n';
        camera += "Fov: " + std::to_string(this->fov) + " Near: " + std::to_string(this->near) + " Far: " + std::to_string(this->far) + '\n';

        /* Devolução da string construída */
        return camera;
    }
}
