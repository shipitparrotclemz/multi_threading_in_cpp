cmake_minimum_required(VERSION 3.12)

project(MultiThreadingPractice)

set(SOURCE_FILES vanilla_threads.cpp)
set(HEADER_FILES vanilla_threads.h)

# Use C++14
# Q: Why tho?
# A: We are using std::literals::chrono_literals, and that is introduced in c++14
set(CMAKE_CXX_STANDARD 14)

# creates an executable "VanillaThreads"
add_executable(VanillaThreads ${SOURCE_FILES} ${HEADERFILES})