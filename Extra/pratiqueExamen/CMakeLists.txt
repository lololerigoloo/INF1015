cmake_minimum_required(VERSION 3.16)

project(MatriceProjet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Récupère tous les .cpp et .hpp du dossier

file(GLOB SRC_FILES "*.cpp" "*.hpp")

add_executable(MatriceProjet ${SRC_FILES})
