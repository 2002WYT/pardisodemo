project(subzero)
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O3")
add_subdirectory(src)
include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# include 头文件
include_directories(
  ${catkin_INCLUDE_DIRS}
  /opt/intel/oneapi/mkl/2024.1/include/
)
# 链接库目录
link_directories(
  ${catkin_LIB_DIRS}
  /opt/intel/oneapi/mkl/2024.1/lib/
 )
 link_directories(
  ${catkin_LIB_DIRS}
  /opt/intel/oneapi/compiler/2024.1/lib/
 )

add_executable(app 01.cpp)

target_link_libraries(app SRC)
target_link_libraries(app libmkl_rt.so)
target_link_libraries(app libiomp5.so)


