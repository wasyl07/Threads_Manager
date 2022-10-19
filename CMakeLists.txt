cmake_minimum_required(VERSION 3.0.0)
project(Thread_manager_dev VERSION 0.1.0)

include(CTest)
enable_testing()


add_executable(Thread_manager_dev main.cpp Task_Manager.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
