cmake_minimum_required(VERSION 3.20)
project(LRUCache)
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")  // 设定源文件的路径
add_executable(
    main
    ${SOURCE}
)


target_include_directories(
    main
    ${PROJECT_SOURCE_DIR}/src/include
)
