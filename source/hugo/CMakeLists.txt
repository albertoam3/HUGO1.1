cmake_minimum_required(VERSION 3.1)

project(source LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Gui 5.4 REQUIRED)



set(CMAKE_PREFIX_PATH "/home/urjcadmin/Code/nsol/build" ${CMAKE_PREFIX_PATH})

find_package(nsol REQUIRED)

list( APPEND HUGO_DEPENDENT_LIBRARIES
        Qt5::Widgets
        Qt5::Gui
        Qt5::OpenGL
        GL
        nsol
        )


add_executable(hugo
        resources.qrc
        hugo.cpp
        mainwindow.cpp
        mainwindow.h
        myOpenGLWidget.cpp
        myOpenGLWidget.h
        mainwindow.ui
        myOpenGLWidget2D.h
        myOpenGLWidget2D.cpp
        graphics/graphicObjects.h
        graphics/neuronG.h
        graphics/neuronG.cpp
        graphics/somaG.h
        graphics/somaG.cpp
        graphics/axonG.h
        graphics/axonG.cpp
        graphics/neuriteG.h
        graphics/neuriteG.cpp
        graphics/dendriteG.h
        graphics/dendriteG.cpp
          graphics/sectionH.h
          graphics/sectionH.cpp
        baseDatosObjetos.cpp
        baseDatosObjetos.h graphics/VarEstado.h graphics/VarLongitud.h
        graphics/VarPosDendritas.h
        openGLDialog.cpp
        openGLDialog.h)

target_link_libraries(hugo ${HUGO_DEPENDENT_LIBRARIES})
