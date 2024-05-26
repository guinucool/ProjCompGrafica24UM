# Definição da versão miníma necessária para compilar este cmake
cmake_minimum_required(VERSION 3.5)

# Inicialização do projeto que irá definir o gerador
project(generator)

# Lista de módulos partilhados necessários ao funcionamento do programa
set(SHARED_SRC_FILES)
list(APPEND SHARED_SRC_FILES
     ../shared/src/utils/matrix.cpp
     ../shared/src/geometry/point.cpp
     ../shared/src/geometry/face.cpp
     ../shared/src/geometry/primitive.cpp
     ../shared/src/texture/coordinates.cpp
    )

# Lista de módulos necessários para o funcionamento da geração de primitivas do programa
set(GENERATOR_SRC_FILES)
file(GLOB GENERATOR_PRIMITIVE_SRC "src/primitives/*.cpp")
list(APPEND GENERATOR_SRC_FILES ${GENERATOR_PRIMITIVE_SRC})

# Lista de módulos necessários para o funcionamento da geração de patches do programa
file(GLOB GENERATOR_PATCH_SRC "src/patches/*.cpp")
list(APPEND GENERATOR_SRC_FILES ${GENERATOR_PATCH_SRC})

# Lista de ficheiros necessários à definição dos geradores de modelos em específico
file(GLOB MODEL_SOURCES "src/models/*.cpp")
list(APPEND GENERATOR_SRC_FILES ${MODEL_SOURCES})

# Criação do executável do projeto
add_executable(${PROJECT_NAME} 
                src/generator.cpp
                ${SHARED_SRC_FILES}
                ${GENERATOR_SRC_FILES}
            )