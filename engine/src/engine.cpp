/* Inclusão de módulos necessários à funcionalidade do programa */
#include "../inc/containers/world.hpp"
#include <iostream>
#include <IL/il.h>

/* Função principal do programa */
int main(int argc, char** argv) {

	/* Inicialização do DevIL */
	ilInit();

	/* Caso o número de argumentos seja inválido */
	if (argc != 2) {
		std::cerr << "Error: given invalid arguments!" << std::endl;
		return 1;
	}

	/* Conversão do caminho para o xml para string */
	std::string path(argv[1]);

	try {

		/* Inicialização do mundo a ser representado */
		containers::World world(path);

		/* Definição do mundo como sendo o para representar */
		world.setGlobal();

		/* Inicialização do GLUT */
		containers::World::init(argc, argv, containers::World::initDraw);

	} catch(const std::exception& e) {

		/* Impressão do erro obtido */
		std::cerr << "Error: " << e.what() << '!' << std::endl;

		/* Conclusão mal sucedida do programa */
		return 1;
	}

	/* Conclusão bem sucedida do programa */
	return 0;
}