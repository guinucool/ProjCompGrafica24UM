# Definição da versão miníma necessária para compilar este cmake
cmake_minimum_required(VERSION 3.5)

# Inicialização do projeto que irá definir o motor gráfico
project(engine)

# Lista de módulos partilhados necessários ao funcionamento do programa
set(SHARED_SRC_FILES)
list(APPEND SHARED_SRC_FILES
     ../shared/src/geometry/point.cpp
     ../shared/src/geometry/face.cpp
     ../shared/src/geometry/primitive.cpp
     ../shared/src/utils/matrix.cpp
     ../shared/src/exception/unvalues.cpp
    )

# Lista de módulos necessários para o funcionamento do desenho de primitivas do programa
set(ENGINE_SRC_FILES)
file(GLOB GENERATOR_DRAWABLE_SRC "src/drawables/*.cpp")
list(APPEND ENGINE_SRC_FILES ${GENERATOR_DRAWABLE_SRC})

# Lista de módulos necessários para a transformação do desenho do programa
file(GLOB_RECURSE GENERATOR_TRANSFORM_SRC "src/transforms/*.cpp")
list(APPEND ENGINE_SRC_FILES ${GENERATOR_TRANSFORM_SRC})

# Lista de módulos necessários para a projeção do desenho do programa
file(GLOB GENERATOR_PROJECTION_SRC "src/projection/*.cpp")
list(APPEND ENGINE_SRC_FILES ${GENERATOR_PROJECTION_SRC})

# Lista de módulos necessários para a contenção de objetos do programa
file(GLOB GENERATOR_CONTAINER_SRC "src/containers/*.cpp")
list(APPEND ENGINE_SRC_FILES ${GENERATOR_CONTAINER_SRC})

# Lista de módulos externos necessários
set(EXTERNAL_SRC_FILES)
list(APPEND EXTERNAL_SRC_FILES
     ../external/tinyxml2/tinyxml2.cpp
    )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Criação do executável do projeto
add_executable(${PROJECT_NAME} 
                src/engine.cpp
                ${SHARED_SRC_FILES}
                ${ENGINE_SRC_FILES}
                ${EXTERNAL_SRC_FILES}
            )

# Definição de preferência do OpenGL
set(OpenGL_GL_PREFERENCE "GLVND")

# Inclusão do OpenGL e do GLUT no projeto
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if  (WIN32)

    message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
    set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")
    
    if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
        message(ERROR ": GLUT not found")
    endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")	
    
    if (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")
        message(ERROR ": GLEW not found")
    endif (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")	

    
    include_directories(${TOOLKITS_FOLDER}/glut ${TOOLKITS_FOLDER}/glew)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} 
                                            ${TOOLKITS_FOLDER}/glut/glut32.lib 
                                            ${TOOLKITS_FOLDER}/glew/glew32.lib )
    
    if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll"  AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll"  AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll")	
    
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    
else (WIN32) #Linux and Mac

    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")

    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
    
    if (NOT APPLE)
        find_package(GLEW REQUIRED)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
        target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
    else (NOT APPLE)
        target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
    endif(NOT APPLE)

    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
    if(NOT GLUT_FOUND)
        message(ERROR ": GLUT not found!")
    endif(NOT GLUT_FOUND)
    
endif(WIN32)