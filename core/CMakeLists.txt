cmake_minimum_required(VERSION 3.10)
project(sonus_core)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/audio_encoder.cpp
    src/audio_decoder.cpp
)

# Add header files
set(HEADERS
    include/sonus/audio_encoder.hpp
    include/sonus/audio_decoder.hpp
)

# Create library
add_library(sonus_core STATIC ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(sonus_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Set output directories
set_target_properties(sonus_core PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Install rules
install(TARGETS sonus_core
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/sonus
    DESTINATION include
) 