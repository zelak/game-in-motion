cmake_minimum_required(VERSION 2.8.8)

# project name
set(PROJECT_NAME gameinmotion)
project(${PROJECT_NAME})

# boost
find_package(Boost 1.68.0 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#ffmpeg
find_package(FFmpeg COMPONENTS AVFORMAT REQUIRED)
include_directories(${FFmpeg_INCLUDE_DIRS})

# enable C++11
SET(CMAKE_CXX_FLAGS "-std=c++11")

# source files
file(GLOB SOURCES "src/*.cc")

# version file
file(WRITE src/version.h "char __GAMEINMOTION_VERSION__[] = \"0.1.0\";")

# executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${FFMPEG_LIBRARIES})