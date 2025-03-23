cmake_minimum_required(3.22)
project(cmake_usage_demo_project)
add_subdirectory(src)
add_subdirectory(lib)
# 生成静态库
add_library(my_static_lib STATIC src/utils.cpp include/utils.h)
# 生成动态文件库
add_library(my_shared_lib SHARED src/utils.cpp include/utils.h)
# 头文件路径
target_include_directories(my_static_lib PUBLIC ../include)
target_include_directories(my_shared_lib PUBLIC ../include)


add_executable(my_app main.cpp)

target_link_libraries(
    my_app
    my_static_lib
    my_shared_lib
    GTest::gtest
)

