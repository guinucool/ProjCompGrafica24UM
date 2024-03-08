/* Inclusão de módulos necessários à funcionalidade do programa */
#include "../inc/models/sphere.hpp"
#include <iostream>
#include <string>

/* Função principal do programa */
int main(int argc, char ** argv) {

    /* Verificação do número de argumentos */
    if (argc < 2) {

        /* Emitir a mensagem de erro */
        std::cerr << "Error: given invalid arguments!" << std::endl;

        /* Conclusão do programa em erro */
		return 1;
    }

    /* Obtenção do primeiro argumento em formato string */
    std::string model(argv[1]);

    models::Sphere sphere(3, 10, 10);

    std::cout << sphere.toString();
    
    std::ofstream stream("object.3d", std::ios::binary);

    sphere.write(stream);

    stream.close();

    /* Conclusão do programa em sucesso */
    return 0;
}