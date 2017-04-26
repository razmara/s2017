cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED )
#find_package( libopenni2 REQUIRED )

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}/bin
    )

add_definitions(
    -std=c++11
    )

include_directories(
    $ENV{OPENNI2_INCLUDE}
    )

link_directories(
    $ENV{OPENNI2_REDIST}
    )

link_libraries(
    -lOpenNI2
    ${OpenCV_LIBS}
    )

add_executable(
    template
    src/main.cpp
    )
