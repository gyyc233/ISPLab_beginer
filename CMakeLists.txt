cmake_minimum_required(VERSION 3.20)

project(isp_beginer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

file(GLOB_RECURSE srcs CONFIGURE_DEPENDS ./*.cpp ./*.h)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

add_library(isp_lab STATIC ${srcs})
target_include_directories(isp_lab PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(isp_lab ${OpenCV_LIBS})

# 坏点检测
add_executable(dead_pixel_correction test/dead_pixel_correction.cpp)
target_link_libraries(dead_pixel_correction isp_lab)

# 黑电平补偿
add_executable(black_level_correction test/black_level_correction.cpp)
target_link_libraries(black_level_correction isp_lab)

# 镜头阴影矫正
add_executable(lens_shading_correction test/lens_shading_correction.cpp)
target_link_libraries(lens_shading_correction isp_lab)

add_executable(auto_white_balance test/auto_white_balance.cpp)
target_link_libraries(auto_white_balance isp_lab)

add_executable(rgb_yuv_test test/rgb_yuv_test.cpp)
target_link_libraries(rgb_yuv_test isp_lab)

# copy floder to install path
set(build_data_include ${CMAKE_CURRENT_SOURCE_DIR}/build)
execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory  ${CMAKE_CURRENT_SOURCE_DIR}/data ${build_data_include}/data)
