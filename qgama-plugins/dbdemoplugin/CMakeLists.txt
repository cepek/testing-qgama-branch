cmake_minimum_required(VERSION 3.7)

set(QGPLUGIN dbdemoplugin)

project(${QGPLUGIN} LANGUAGES CXX)

message("-- Linking ${QGPLUGIN}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMAKE_PREFIX_PATH By default this is empty. It is intended to be set by the project.
#
#set(CMAKE_PREFIX_PATH "/home/cepek/Qt/5.15.0/gcc_64/lib/cmake/Qt6/") # example linux
#set(CMAKE_PREFIX_PATH "C:/Qt/5.15.0/msvc2019_64/lib/cmake/Qt6/")     # example windows

find_package(Qt6 COMPONENTS Core Gui Sql Widgets REQUIRED)

set(QGPATH "../../qgama")
include_directories(${QGPATH})

add_library(${QGPLUGIN} SHARED
  ${QGPATH}/qgamainterfaces.h
  ${QGPLUGIN}.cpp
  ${QGPLUGIN}.h
)

target_link_libraries(${QGPLUGIN} PRIVATE
  Qt6::Core Qt6::Gui Qt6::Sql Qt6::Widgets
)

target_compile_definitions(${QGPLUGIN} PRIVATE ${QGPLUGIN}_LIBRARY)

set_target_properties(${QGPLUGIN} PROPERTIES LINKER_LANGUAGE CXX)
