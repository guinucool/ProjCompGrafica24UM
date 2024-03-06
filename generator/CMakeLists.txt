cmake_minimum_required(VERSION 3.5)

project(generator)

# Lista de módulos necessários para o funcionamento da geração de primitivas do programa
set(GENERATOR_SRC_FILES)
list(APPEND GENERATOR_SRC_FILES
     ../shared/src/utils/matrix.cpp
     src/primitives/face.cpp
     src/primitives/point.cpp
     src/primitives/primitive.cpp
    )

# Lista de ficheiros necessários à definição dos geradores de modelos em específico
set(GENERATOR_SRC_MODELS_FILES)
file(GLOB MODEL_SOURCES "src/models/*.cpp")
list(APPEND GENERATOR_SRC_MODELS_FILES ${MODEL_SOURCES})

# Criação do executável do projeto
add_executable(${PROJECT_NAME} 
                src/generator.cpp
                ${GENERATOR_SRC_FILES}
                ${MODEL_SOURCES}
            )