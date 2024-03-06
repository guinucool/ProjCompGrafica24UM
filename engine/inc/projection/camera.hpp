#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../../external/tinyxml2/tinyxml2.h"
#include "../drawables/point.hpp"

/* Inicialização do namespace onde a classe irá ser definida */
namespace projection
{

    /* Definição da classe câmera */
    class Camera {

        private:

            /* Definição das propriedades da câmera */
            drawables::Point origin, lookAt, up;
            float fov, near, far;
        
        public:

            /* Construtor padrão de câmera */
            Camera();

            /* Construtor parametrizado de câmera */
            Camera(drawables::Point origin, drawables::Point lookAt, drawables::Point up, float fov, float near, float far);

            /* Construtor de cópia de câmera */
            Camera(const Camera& camera);

            /* Construtor através de um elemento xml */
            Camera(tinyxml2::XMLElement * camera);

            /* Devolução da referência do ponto de origem */
            drawables::Point& Origin();

            /* Devolução da referência do ponto de origem sem possibilidade de alteração */
            const drawables::Point& Origin() const;

            /* Devolução da referência do ponto de vigia */
            drawables::Point& LookAt();

            /* Devolução da referência do ponto de vigia sem possibilidade de alteração */
            const drawables::Point& LookAt() const;

            /* Devolução da referência do "ponto" up */
            drawables::Point& Up();

            /* Devolução da referência do "ponto" up sem possibilidade de alteração */
            const drawables::Point& Up() const;

            /* Definição do valor do fov */
            void setFov(float fov);

            /* Devolução do valor do fov */
            float getFov() const;

            /* Definição do valor do near */
            void setNear(float near);

            /* Devolução do valor do near */
            float getNear() const;

            /* Definição do valor do far */
            void setFar(float far);

            /* Devolução do valor do far */
            float getFar() const;

            /* Leitura de uma câmera através de um ficheiro xml */
            void read(tinyxml2::XMLElement * camera);

            /* Define a câmera que vai ser usada no cenário */
            void defineCamera() const;

            /* Define a função que será usada para definir o tamanho da câmera */
            void shapeCamera(int width, int height) const;

            /* Define o operador de comparação de igualdade */
            bool operator==(const Camera& camera) const;

            /* Define o operador de comparação de desigualdade */
            bool operator!=(const Camera& camera) const;

            /* Define a operação de clonagem de uma câmera */
            Camera clone() const;

            /* Converte a câmera num formato string */
            std::string toString() const;
    };
}

#endif