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



set(CMAKE_PREFIX_PATH "/home/alberto/hbp/nsol/build" ${CMAKE_PREFIX_PATH})

find_package(nsol REQUIRED)

list( APPEND HUGO_DEPENDENT_LIBRARIES
        Qt5::Widgets
        Qt5::Gui
        Qt5::OpenGL
        GL
        nsol
        )


add_executable(hugo
          hugo.cpp
          mainwindow.cpp
          mainwindow.h
          myopenglwidget.cpp
          myopenglwidget.h
          mainwindow.ui
          myopenglwidget2d.h
          myopenglwidget2d.cpp
          objetos/axon.cpp
          objetos/axon.h
          objetos/dendrites.cpp
          objetos/dendrites.h
          objetos/soma.h
          objetos/soma.cpp
          objetos/objetos.h
          objetos/neuron.cpp
          objetos/neuron.h
          graphics/graphic_objects.h
          graphics/neuron_g.h
          graphics/neuron_g.cpp
          graphics/soma_g.h
          graphics/soma_g.cpp
          graphics/axon_g.h
          graphics/axon_g.cpp
          graphics/neurite_g.h
          graphics/neurite_g.cpp
          graphics/dendrite_g.h
          graphics/dendrite_g.cpp
          graphics/sectionH.h
          graphics/sectionH.cpp
          base_datos_objetos.cpp 
          base_datos_objetos.h  graphics/VariableEstado.h)

target_link_libraries(hugo ${HUGO_DEPENDENT_LIBRARIES})
