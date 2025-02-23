cmake_minimum_required(VERSION 3.22)
project(string_implement)
set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")  # 搜索在src目录下所有以cpp为结尾的源文件

add_executable(
    main
    ${SOURCES}
)

# 设置为目标文件寻找头文件的目录
target_include_directories(
    main
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/include
)

