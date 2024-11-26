cmake_minimum_required(VERSION 3.27)
project(lab_lin C)

set(CMAKE_C_STANDARD 11)

include_directories(lab_lin-master)

add_executable(server
        lab_lin-master/server.c
        lab_lin-master/erproc.c
        lab_lin-master/erproc.h
)

# Создаём клиент
add_executable(client
        lab_lin-master/client.c
        lab_lin-master/erproc.c
        lab_lin-master/erproc.h
)

