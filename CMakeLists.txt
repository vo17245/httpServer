cmake_minimum_required(VERSION 3.1)
project(http_server)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
add_executable(http_server main.cpp HttpRequest.cpp MySocket.cpp tools.cpp Server.cpp MyEpoll.cpp HttpResponse.cpp Log.cpp) 
