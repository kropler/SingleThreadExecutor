cmake_minimum_required(VERSION 3.15)
project(SingleThreadExecutor)

set(CMAKE_CXX_STANDARD 11)

add_executable(SingleThreadExecutor main.cpp Timer.cpp Threadsafe_queue.cpp SingleThreadExecutor.cpp)
