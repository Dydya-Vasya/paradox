cmake_minimum_required(VERSION 3.14)
project(paradox-dspirit VERSION 1.0.0 LANGUAGES CXX)

# Кроссплатформенные настройки
if(MSVC)
    # Windows settings
    add_compile_options(/W4 /MP)
    add_definitions(-DNOMINMAX -D_CRT_SECURE_NO_WARNINGS -DPARADOX_DSPIRIT_EXPORTS)
else()
    # Linux/macOS settings
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(NOT APPLE)
        add_compile_options(-Werror)
    endif()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main library
add_library(paradox-dspirit
    src/dspirit.cpp
)

# Include directories
target_include_directories(paradox-dspirit
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Alias
add_library(paradox::dspirit ALIAS paradox-dspirit)

# Simple test
add_executable(test_example examples/test.cpp)
target_link_libraries(test_example paradox::dspirit)

message(STATUS "========================================")
message(STATUS "paradox-dspirit ${PROJECT_VERSION}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "========================================")