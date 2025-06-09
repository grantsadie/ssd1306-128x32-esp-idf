cmake_minimum_required(VERSION 3.5)

file(GLOB COMPONENT_SRCS src/*.cpp)
file(GLOB COMPONENT_INCS include/*.h)

idf_component_register(SRCS ${COMPONENT_SRCS}
                       INCLUDE_DIRS ${COMPONENT_INCS}
                       REQUIRES )

project(ssd1306_display)
