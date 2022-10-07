cmake_minimum_required(VERSION 3.17)

project(bomberman)

if(UNIX)
    set(CMAKE_CXX_FLAGS "-std=c++17 -W -Wall -Wextra")
endif(UNIX)

if(win32)
    endif(win32)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(
                    src/bomb
					src/vector
					src/gui
					src/save
					src/color
                    src/game
					src/rectangle
                    src/error
                    src/menu
                    src/music
                    src/raylib
                    src/map
                    src/player
                    src/core
                    src/power
                    src/image)

FILE(GLOB SRC_FILES
        src/bomb/*.cpp
		src/vector/*.cpp
		src/color/*.cpp
		src/rectangle/*.cpp
        src/game/*.cpp
        src/error/*.cpp
		src/gui/*.cpp
        src/menu/*.cpp
        src/music/*.cpp
        src/raylib/*.cpp
        src/map/*.cpp
        src/save/*.cpp
        src/player/*.cpp
        src/image/*.cpp
        src/core/*.cpp
        src/power/*.cpp)

add_executable(bomberman ${SRC_FILES})

find_package(raylib 3.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} raylib)