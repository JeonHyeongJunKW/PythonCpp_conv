cmake_minimum_required(VERSION 3.15)
project(python_cpp)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE Release)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )

find_package(Boost REQUIRED COMPONENTS thread)
find_package(OpenCV REQUIRED)

add_executable(Example1 ../Example1/main.cpp)
target_link_libraries(Example1 ${PYTHON_LIBRARIES} ${OpenCV_LIBS})

add_executable(Example2 ../Example2/main.cpp)
target_link_libraries(Example2 ${PYTHON_LIBRARIES} ${OpenCV_LIBS})
