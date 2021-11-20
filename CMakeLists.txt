cmake_minimum_required(VERSION 3.16)
project(signature)

set(CMAKE_CXX_STANDARD 17)

include_directories(${BOOST_INCLUDE_PATH})
link_directories(${BOOST_LIBRARY_PATH})

add_executable(signature src/main.cpp src/Config.cpp src/Reader.cpp src/Writer.cpp src/ThreadPool.cpp src/Signature.cpp src/SharedQueue.h)

target_link_libraries(${PROJECT_NAME} pthread)