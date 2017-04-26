cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH})

#include (FindPkgConfig)

find_package( OpenCV REQUIRED )
find_package( OpenNI2 REQUIRED )


set(    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}/bin    )

add_definitions(
    -std=c++11
    )

include_directories(
#    $ENV{OPENNI2_INCLUDE}
    ${OPENNI2_INCLUDE_DIRS}
    )
#
# link_directories(
#    $ENV{OPENNI2_REDIST}
#    )
#
link_libraries(
    #-lOpenNI2
    ${OPENNI_LIBRARIES} 
    ${OpenCV_LIBS}
    )

add_executable(
    template
    src/main.cpp
    )
