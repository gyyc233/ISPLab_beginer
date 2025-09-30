cmake_minimum_required(VERSION 3.20)

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

add_executable(dead_pixel_correction test/dead_pixel_correction.cpp)
target_link_libraries(dead_pixel_correction isp_lab)

# copy floder to install path
set(build_data_include ${CMAKE_CURRENT_SOURCE_DIR}/build)
execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory  ${CMAKE_CURRENT_SOURCE_DIR}/data ${build_data_include}/data)
