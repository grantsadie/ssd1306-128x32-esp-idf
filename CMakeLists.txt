cmake_minimum_required(VERSION 3.5)

# Enable C++ support for this component
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB COMPONENT_SRCS src/*.cpp)

idf_component_register(SRCS "src/ssd1306_display.cpp"
                       INCLUDE_DIRS "include"
                       REQUIRES driver)

