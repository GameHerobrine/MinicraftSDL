cmake_minimum_required(VERSION 3.5)
project(minicraft-sdl LANGUAGES C)

add_compile_options(-Wno-implicit-function-declaration) #TODO delete this
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDLmain -lSDL")

file(GLOB_RECURSE SOURCES *.c)
file(GLOB_RECURSE HEADERS *.h)

add_executable(minicraft-sdl ${SOURCES} ${HEADERS})
target_include_directories(minicraft-sdl PUBLIC ".")

