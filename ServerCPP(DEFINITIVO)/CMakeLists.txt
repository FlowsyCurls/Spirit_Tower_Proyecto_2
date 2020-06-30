cmake_minimum_required(VERSION 3.16)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server src/server.cpp src/algorithms/A_Star.h src/algorithms/Bresenham.h src/algorithms/Bresenham.cpp src/Controller/GameManager.cpp src/Controller/GameManager.h src/Model/Board/Board.cpp src/Model/Board/Board.h src/Model/Board/Cell.cpp src/Model/Board/Cell.h src/Model/Board/Entity.cpp src/Model/Board/Entity.h src/Model/Spectres/Spectre.cpp src/Model/Spectres/Spectre.h src/Model/Spectres/RedSpectre.cpp src/Model/Spectres/RedSpectre.h src/Model/Spectres/GraySpectre.cpp src/Model/Spectres/GraySpectre.h src/Model/SimpleEnemies/SpectralEye.cpp src/Model/SimpleEnemies/SpectralEye.h src/Model/SimpleEnemies/Mouse.cpp src/Model/SimpleEnemies/Mouse.h src/Model/SimpleEnemies/Chuchu.cpp src/Model/SimpleEnemies/Chuchu.h src/Model/Objects/Jarron.cpp src/Model/Objects/Jarron.h src/Model/Objects/Treasure.cpp src/Model/Objects/Treasure.h src/Model/Spectres/BlueSpectre.cpp src/Model/Spectres/BlueSpectre.h src/Model/Board/Direction.cpp src/Model/Board/Direction.h src/Model/SimpleEnemies/SimpleEnemy.cpp src/Model/SimpleEnemies/SimpleEnemy.h src/Model/Objects/Objeto.cpp src/Model/Objects/Objeto.h)
if(WIN32)
    target_link_libraries(Server wsock32 ws2_32)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Server Threads::Threads)