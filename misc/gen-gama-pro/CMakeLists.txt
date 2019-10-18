cmake_minimum_required(VERSION 3.10)
project(gama-qt-projects-generators)

add_executable(gama-local-pro gama-local-pro.cpp)
target_compile_definitions(gama-local-pro PRIVATE GAMA_LOCAL_PRO=1)

add_executable(gama-pri gama-local-pro.cpp )
target_compile_definitions(gama-pri PRIVATE GAMA_PRI=1)
