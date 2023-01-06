cmake_minimum_required(VERSION 3.0.0)
project(Thread_manager_dev VERSION 0.1.0)

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Thread_manager_dev src/main.cpp src/Task_Manager.cpp  src/Task.cpp)

target_link_libraries( Thread_manager_dev ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
