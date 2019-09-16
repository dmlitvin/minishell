cmake_minimum_required(VERSION 3.10.2)

project(minishell C)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wextra -Werror")

add_executable(minishell main.c env.c minishell_split.c execute.c built_ins1.c built_ins2.c expansion.c find_executable.c)

add_library(libft STATIC IMPORTED)
set_target_properties(libft PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libft/libft.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/libft/include)

target_link_libraries(minishell libft)
