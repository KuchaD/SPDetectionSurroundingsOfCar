cmake_minimum_required(VERSION 3.10)
project(PROJEKT)

set(CMAKE_CXX_STANDARD 11)
set(OpenCV_STATIC ON)
add_executable(PROJEKT main.cpp)



find_package( OpenCV REQUIRED )
target_link_libraries(PROJEKT ${OpenCV_LIBS})

FIND_LIBRARY(MY_LIB libdlib.a)
TARGET_LINK_LIBRARIES(PROJEKT ${MY_LIB})

