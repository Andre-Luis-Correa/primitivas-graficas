cmake_minimum_required(VERSION 3.27)
project(primitivasGraficas C)

set(CMAKE_C_STANDARD 11)

# Incluir diretório de headers do SDL2
include_directories("${CMAKE_SOURCE_DIR}/SDL2-2.32.10/x86_64-w64-mingw32/include")

# Adicionar executável
add_executable(primitivasGraficas
        main.c
        midpoint_line_algorithm.h
        midpoint_line_algorithm.c
        drawing_utils.h
        drawing_utils.c
        sdl_utils.h
        sdl_utils.c
        main_utils.h
        main_utils.c
)

# Linkar bibliotecas do SDL2
target_link_libraries(primitivasGraficas
        mingw32
        "${CMAKE_SOURCE_DIR}/SDL2-2.32.10/x86_64-w64-mingw32/lib/libSDL2main.a"
        "${CMAKE_SOURCE_DIR}/SDL2-2.32.10/x86_64-w64-mingw32/lib/libSDL2.dll.a"
)

# Copiar SDL2.dll para a pasta de build
add_custom_command(TARGET primitivasGraficas POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/SDL2-2.32.10/x86_64-w64-mingw32/bin/SDL2.dll"
        $<TARGET_FILE_DIR:primitivasGraficas>
)