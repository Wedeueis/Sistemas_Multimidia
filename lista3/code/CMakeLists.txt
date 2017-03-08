cmake_minimum_required(VERSION 2.8)

project(atividade3_1)
add_executable(atividade3_1 "atividade3_1.cpp")
add_executable(atividade3_2 "atividade3_2.cpp")
add_executable(atividade3_3 "atividade3_3.cpp")
add_executable(atividade3_4 "atividade3_4.cpp")
add_executable(atividade3_5 "atividade3_5.cpp")
add_executable(atividade3_6 "atividade3_6.cpp")
add_executable(atividade3_7 "atividade3_7.cpp")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

find_package(OpenCV REQUIRED)

target_link_libraries(atividade3_1 ${OpenCV_LIBS})
target_link_libraries(atividade3_2 ${OpenCV_LIBS})
target_link_libraries(atividade3_3 ${OpenCV_LIBS})
target_link_libraries(atividade3_4 sndfile)
target_link_libraries(atividade3_5 sndfile)
target_link_libraries(atividade3_6 sndfile)
target_link_libraries(atividade3_7 sndfile)
