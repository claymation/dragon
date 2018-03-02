cmake_minimum_required(VERSION 3.0)

project(dragon)

set(CMAKE_CXX_STANDARD 11)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Build library
set(LIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/preprocessor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/streamfilter.cpp
)
add_library(dragon STATIC ${LIB_SOURCES})

# Make test executable
set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/lib/preprocessor_test.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch dragon)