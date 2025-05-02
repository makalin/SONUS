cmake_minimum_required(VERSION 3.10)
project(sonus_tests)

# Find GTest package
find_package(GTest REQUIRED)

# Add test executable
add_executable(sonus_tests test_audio.cpp)

# Link against GTest and our core library
target_link_libraries(sonus_tests
    PRIVATE
        GTest::GTest
        GTest::Main
        sonus_core
)

# Include directories
target_include_directories(sonus_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/../include
)

# Set output directory
set_target_properties(sonus_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Add test
add_test(NAME sonus_tests COMMAND sonus_tests) 