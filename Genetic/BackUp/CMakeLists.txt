cmake_minimum_required(VERSION 3.16)
project(BackUp)

set(CMAKE_CXX_STANDARD 14)

add_executable(BackUp main.cpp Genetic/Entity.cpp Genetic/Entity.h Genetic/Spectrum.cpp Genetic/Spectrum.h Genetic/GeneticManager.cpp Genetic/GeneticManager.h Genetic/LinkedList.h Genetic/Selection.cpp Genetic/Selection.h Genetic/Crossbreed.cpp Genetic/Crossbreed.h Tools/Utility.cpp Tools/Utility.h)