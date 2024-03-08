/* Inclusão de módulos necessários à funcionalidade do programa */
#include "../inc/models/sphere.hpp"
#include "../inc/models/plane.hpp"
#include "../inc/models/cone.hpp"
#include "../inc/models/box.hpp"
#include "../inc/models/cylinder.hpp"
#include <stdexcept>
#include <iostream>
#include <string>

/* Função de criação da esfera */
primitives::Primitive sphere(int argc, char ** argv) {
    
    /* Validação da quantidade de elementos */
    if (argc != 6)
        throw std::invalid_argument("given invalid arguments");

    /* Inicialização e transformação das propriedades */
    float radius = std::stof(argv[2]);
    int slices = std::stoi(argv[3]);
    int stacks = std::stoi(argv[4]);

    /* Devolução do plano criado */
    return models::Sphere(radius, slices, stacks);
}

primitives::Primitive cylinder(int argc, char ** argv) {
    
    /* Validação da quantidade de elementos */
    if (argc != 7)
        throw std::invalid_argument("given invalid arguments");

    /* Inicialização e transformação das propriedades */
    float radius = std::stof(argv[2]);
    float height = std::stof(argv[3]);
    int slices = std::stoi(argv[4]);
    int stacks = std::stoi(argv[5]);

    /* Devolução do plano criado */
    return models::Cylinder(radius, height, slices, stacks);
}

/* Função de criação do cone */
primitives::Primitive cone(int argc, char ** argv) {
    
    /* Validação da quantidade de elementos */
    if (argc != 7)
        throw std::invalid_argument("given invalid arguments");

    /* Inicialização e transformação das propriedades */
    float radius = std::stof(argv[2]);
    float height = std::stof(argv[3]);
    int slices = std::stoi(argv[4]);
    int stacks = std::stoi(argv[5]);

    /* Devolução do plano criado */
    return models::Cone(radius, height, slices, stacks);
}

/* Função de criação da caixa */
primitives::Primitive box(int argc, char ** argv) {
    
    /* Validação da quantidade de elementos */
    if (argc != 5)
        throw std::invalid_argument("given invalid arguments");

    /* Inicialização e transformação das propriedades */
    float length = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);

    /* Devolução do plano criado */
    return models::Box(length, divisions);
}

/* Função de criação do plano */
primitives::Primitive plane(int argc, char ** argv) {
    
    /* Validação da quantidade de elementos */
    if (argc != 5)
        throw std::invalid_argument("given invalid arguments");

    /* Inicialização e transformação das propriedades */
    float length = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);

    /* Devolução do plano criado */
    return models::Plane(length, divisions);
}

/* Função principal do programa */
int main(int argc, char ** argv) {

    /* Verificação do número de argumentos */
    if (argc < 3) {

        /* Emitir a mensagem de erro */
        std::cerr << "Error: given invalid arguments!" << std::endl;

        /* Conclusão do programa em erro */
		return 1;
    }

    /* Obtenção do primeiro argumento em formato string */
    std::string model(argv[1]);

    /* Variável placeholder do modelo a ser transformado em ficheiro */
    primitives::Primitive primitive;

    /* Variável placeholder do caminho onde vai ser guardado o modelo */
    std::string path(argv[argc - 1]);

    try {

        /* Verifica qual o modelo escolhido para representação */
        if (model == "plane")
            primitive = plane(argc, argv);
        else if (model == "box")
            primitive = box(argc, argv);
        else if (model == "cone")
            primitive = cone(argc, argv);
        else if (model == "sphere")
            primitive = sphere(argc, argv);
        else if (model == "cylinder")
            primitive = cylinder(argc, argv);
        else
            throw std::invalid_argument("given invalid arguments");

        /* Armazenamento da primitiva em ficheiro */
        primitive.write(path);

    } catch(const std::exception& e) {

        /* Emite a mensagem de erro */
        std::cerr << "Error: " << e.what() << '!' << std::endl;

        /* Conclusão do programa em erro */
        return 1;
    }

    /* Conclusão do programa em sucesso */
    return 0;
}