cmake_minimum_required (VERSION 2.8.3)
project(vtec)

SET(CMAKE_VERBOSE_MAKEFILE ON)

add_definitions(-std=c++11 -fPIC)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(include)

find_library(VTEC
	NAMES libhomography_optimizer.so
	HINTS ${PROJECT_SOURCE_DIR}/lib)

find_package(OpenCV)
find_package(OpenCV REQUIRED COMPONENTS xfeatures2d)
message( "Opencv version found: " ${OpenCV_PACKAGE_VERSION} )
message( "Opencv libraries found: " ${OpenCV_LIBRARIES} )

add_executable(ibg_tracker_example src/ibg_tracker_example.cpp)
target_link_libraries(ibg_tracker_example ${VTEC} ${OpenCV_LIBRARIES})

add_executable(ibg_tracker_with_predictor_example src/ibg_tracker_with_predictor_example.cpp)
target_link_libraries(ibg_tracker_with_predictor_example ${VTEC} ${OpenCV_LIBRARIES})

add_executable(ibg_tracker_robust_example src/ibg_tracker_robust_example.cpp)
target_link_libraries(ibg_tracker_robust_example ${VTEC} ${OpenCV_LIBRARIES})

add_executable(ibg_optimize_homography_example src/ibg_optimize_homography_example.cpp)
target_link_libraries(ibg_optimize_homography_example ${VTEC} ${OpenCV_LIBRARIES})

add_executable(unified_tracker_example src/unified_tracker_example.cpp)
target_link_libraries(unified_tracker_example ${VTEC} ${OpenCV_LIBRARIES})


# GET_TARGET_PROPERTY( FULL_LIBRARY_NAME ${PROJECT_NAME} LOCATION )
SET(vtec_LIBRARY_DIR ${PROJECT_BINARY_DIR} )
SET(vtec_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/vtecConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/vtecConfig.cmake @ONLY IMMEDIATE )

export(PACKAGE vtec)

INSTALL(DIRECTORY include/homography_optimizer DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN "*.h" )
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/lib/  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ) 
# trailing / on source dir is needed: https://cmake.org/cmake/help/v3.16/command/install.html#installing-directories The last component of each directory name is appended to the destination directory but a trailing slash may be used to avoid this because it leaves the last component empty.
