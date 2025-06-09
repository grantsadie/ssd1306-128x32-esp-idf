cmake_minimum_required(VERSION 3.5)

file(GLOB COMPONENT_SRCS src/*.cpp)
# file(GLOB COMPONENT_INCS "include")

idf_component_register(SRCS "src/ssd1306_display.cpp"
                       INCLUDE_DIRS "include"
                       REQUIRES driver)

# project(ssd1306_display)

