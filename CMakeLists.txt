cmake_minimum_required(VERSION 3.10)
project(csv_analyzer_cpp)

set(CMAKE_CXX_STANDARD 17)

# Include vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

enable_testing()
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES src/analyzer.cpp)
add_executable(csv_analyzer_cpp ${SOURCES} src/main.cpp)

target_link_libraries(csv_analyzer_cpp)

add_definitions(-DTEST_DATA_PATH=\"${CMAKE_SOURCE_DIR}/tests/test_data\")

find_package(GTest CONFIG REQUIRED)
file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(tests ${TEST_SOURCES} ${SOURCES})

target_link_libraries(tests GTest::gtest GTest::gtest_main)

add_test(NAME csv_analyzer_tests COMMAND tests)
