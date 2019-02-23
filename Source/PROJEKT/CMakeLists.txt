cmake_minimum_required(VERSION 3.10)
project(PROJEKT)

set(CMAKE_CXX_STANDARD 11)
set(OpenCV_STATIC ON)
add_executable(PROJEKT main.cpp utils/Utils.cpp utils/Utils.h src/Network.cpp src/Network.h)



find_package( OpenCV REQUIRED )
target_link_libraries(PROJEKT ${OpenCV_LIBS})

add_library(MY_LIB STATIC IMPORTED libdlib.a)
TARGET_LINK_LIBRARIES(PROJEKT ${MY_LIB})

