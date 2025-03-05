cmake_minimum_required(VERSION 3.20)
project(LRUK VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 查找src目录下的所有.cpp文件
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
# 添加可执行文件
add_executable(
    main
    ${SOURCES}
)
# 为目标添加头文件搜索路径(PRIVATE表示仅对该目标有效)
target_include_directories(main
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/include
)