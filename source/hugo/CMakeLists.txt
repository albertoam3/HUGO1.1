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



set(CMAKE_PREFIX_PATH "/home/alberto/code/nsol/build" ${CMAKE_PREFIX_PATH})

find_package(nsol REQUIRED)

list( APPEND HUGO_DEPENDENT_LIBRARIES
        Qt5::Widgets
        Qt5::Gui
        Qt5::OpenGL
        GL
        nsol
        )

if(ANDROID)
  add_library(hugo SHARED
          hugo.cpp
          mainwindow.cpp
          mainwindow.h
          myopenglwidget.cpp
          myopenglwidget.h
          mainwindow.ui
  )
else()
  add_executable(hugo
          hugo.cpp
          mainwindow.cpp
          mainwindow.h
          myopenglwidget.cpp
          myopenglwidget.h
          mainwindow.ui
          objetos/axon.cpp
          objetos/axon.h
          objetos/dendrites.cpp
          objetos/dendrites.h
          objetos/soma.h
          objetos/soma.cpp
          objetos/objetos.h
          objetos/neuron.cpp
          objetos/neuron.h
          graphics/graphic_neuron.h
          graphics/graphic_neuron.cpp
          graphics/graphic_objects.h
          graphics/graphic_axon.cpp
          graphics/graphic_axon.h 
          graphics/graphic_soma.cpp 
          graphics/graphic_soma.h 
          graphics/graphic_dendrite.cpp
          graphics/neuron_g.h
          graphics/graphic_dendrite.h 
          base_datos_objetos.cpp 
          base_datos_objetos.h)
endif()

target_link_libraries(hugo ${HUGO_DEPENDENT_LIBRARIES})
