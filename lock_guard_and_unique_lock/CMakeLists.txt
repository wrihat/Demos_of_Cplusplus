cmake_minimum_required(VERSION 3.20)
project(LOCK VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(
    main
    ${SOURCES}
)
target_include_directories(
    main
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/include
)
# 总共7行
