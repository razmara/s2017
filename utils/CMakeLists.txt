cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(pcdUtils)

find_package(PCL 1.7 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (pcdTransfrom pcdTransfrom.cpp)
target_link_libraries (pcdTransfrom ${PCL_LIBRARIES})

add_executable (pcdMerge pcdMerge.cpp)
target_link_libraries (pcdMerge ${PCL_LIBRARIES})

add_executable (trajInverse traj_inverse.cpp)
target_link_libraries (trajInverse ${PCL_LIBRARIES})

add_executable (goSorter goSorter.cpp)
target_link_libraries (goSorter ${PCL_LIBRARIES})

