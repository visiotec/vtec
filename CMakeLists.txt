cmake_minimum_required (VERSION 2.8.3)
project(vtec)

SET(CMAKE_VERBOSE_MAKEFILE ON)

add_definitions(-std=c++98)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(include)

find_library(VTEC_CORE
	NAMES libvtec_core.so
	HINTS ${PROJECT_SOURCE_DIR}/lib)

find_library(VTEC_HOMOGRAPHY_OPTIMIZER
	NAMES libhomography_optimizer.so
	HINTS ${PROJECT_SOURCE_DIR}/lib)

add_executable(vtec_ibg_tracker_example src/vtec_ibg_tracker_example.cpp)
target_link_libraries(vtec_ibg_tracker_example ${VTEC_HOMOGRAPHY_OPTIMIZER} ${VTEC_CORE})

add_executable(vtec_ibg_optimize_homography_example src/vtec_ibg_optimize_homography_example.cpp)
target_link_libraries(vtec_ibg_optimize_homography_example ${VTEC_HOMOGRAPHY_OPTIMIZER} ${VTEC_CORE})

# GET_TARGET_PROPERTY( FULL_LIBRARY_NAME ${PROJECT_NAME} LOCATION )
SET(vtec_LIBRARIES ${VTEC_HOMOGRAPHY_OPTIMIZER} ${VTEC_CORE} )
SET(vtec_LIBRARY_DIR ${PROJECT_BINARY_DIR} )
SET(vtec_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/vtecConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/vtecConfig.cmake @ONLY IMMEDIATE )

export(PACKAGE vtec)

INSTALL(DIRECTORY include/homography_optimizer DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN "*.h" )
INSTALL(DIRECTORY include/vtec_core DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN "*.h" )
INSTALL(FILES ${vtec_LIBRARIES} ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )