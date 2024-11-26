cmake_minimum_required(VERSION 3.27)
project(lab_lin C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(server
        src/server.c
        src/erproc.c
        src/erproc.h
)

# Создаём клиент
add_executable(client
        src/client.c
        src/erproc.c
        src/erproc.h
)

