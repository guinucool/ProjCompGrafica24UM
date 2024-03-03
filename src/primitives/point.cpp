#include "../../includes/primitives/point.hpp"
#include "../../includes/utils/matrix.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

/* Inicialização do namespace ao qual a classe pertence */
namespace primitives
{

    /* Definição do objeto de tipo ponto */
    class Point {

        private:

            /* Definição das propriedades do ponto */
            utils::Matrix<float> coords;

            /* Inicialização do vetor de coordenadas do ponto */
            void initCoords() {
                this->coords = utils::Matrix<float>(3, 1);
            }

        public:
        
            /* Construtor vazio que invoca um ponto sempre na origem do referencial */
            Point() {

                /* Inicialização do vetor de coordenadas */
                this->initCoords();

                /* Associação de coordenadas */
                this->setCoords(0.0f, 0.0f, 0.0f);
            }

            /* Construtor parametrizado */
            Point(float x, float y, float z) {

                /* Inicialização do vetor de coordenadas */
                this->initCoords();

                /* Associação das coordenadas */
                this->setCoords(x, y, z);
            }

            /* Construtor de cópia */
            Point(const Point& point) {

                /* Inicialização do vetor de coordenadas */
                this->initCoords();

                /* Associação das coordenadas */
                this->setCoords(point.getX(), point.getY(), point.getZ());
            }

            /* Construtor parametrizado com vetor */
            Point(utils::Matrix<float> vector) {

                /*  */
            }

            /*Point(std::ifstream& stream) {
                stream >> x >> y >> z;
            }*/

            /* Definição do valor das coordenadas de um ponto */
            void setCoords(float x, float y, float z) {

                /* Associação das coordendas à respetiva posição no vetor */
                this->coords[0] = x;
                this->coords[1] = y;
                this->coords[2] = z;
            }

            /* Definição das coordenada x de um ponto */
            void setX(float x) {
                this->coords[0] = x;
            }

            /* Definição das coordenada y de um ponto */
            void setY(float y) {
                this->coords[1] = y;
            }

            /* Definição das coordenada z de um ponto */
            void setZ(float z) {
                this->coords[2] = z;
            }

            /* Definição das coordenadas via vetor */
            void setVector(utils::Matrix<float> vector) {
                this->coords = vector;
            }

            /* Devolução do valor da coordenada x de um ponto */
            float getX() const {
                return this->coords.at(0,0);
            }

            /* Devolução do valor da coordenada y de um ponto */
            float getY() const {
                return this->coords.at(1,0);
            }

            /* Devolução do valor da coordenada z de um ponto */
            float getZ() const {
                return this->coords.at(2,0);
            }

            /* Transformação de um ponto aplicando uma matriz */
            Point transform(float ** transform) const {

            }

            /* Translação sobre os eixos pretendidos */
            Point translateD(float dx, float dy, float dz) const {
                return Point(this->getX() + dx, this->getY() + dy, this->getZ() + dz);
            }

            /* Translação sobre os eixos pretendidos usando coordenadas polares */
            Point translateR(float radius, float beta, float theta) const {



                return Point(this->getX() + dx, this->getY() + dy, this->getZ() + dz);
            }

            /* Rotação de um ponto sobre os eixos pretendidos */
            Point rotate(float angleX, float angleY, float angleZ) const {
                // TODO
            }

        // Operações de leitura e escrita em arquivos
        void write(std::ofstream& stream) const {
            stream << x << " " << y << " " << z << std::endl;
        }

        void read(std::ifstream& stream) {
            stream >> x >> y >> z;
        }

        void draw() const {
            // TODO
        }

        void feedBuffer(float* buffer) {
            // TODO
        }

        bool operator==(const Point& other) const {
            return 
        }

        bool operator!=(const Point& other) const {
            return x == other.x && y == other.y && z == other.z;
        }

        Point clone() const {
            return Point(*this);
        }

        std::string toString() const {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
        }
    };
}