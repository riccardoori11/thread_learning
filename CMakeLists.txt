cmake_minimum_required(VERSION 3.31)

project(SERVER_IN_CPP)


add_executable(server server.cpp)
add_executable(client client.cpp)
add_executable(thread thread.cpp)
add_executable(open open.cpp)
add_executable(async async.cpp)

