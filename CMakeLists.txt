cmake_minimum_required(VERSION 3.14)
project(paradox-dspirit VERSION 1.0.0 LANGUAGES CXX)

# Настройки для Windows
if(WIN32)
    add_compile_options(/W4 /WX /MP)
    add_definitions(-DNOMINMAX -D_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Основная библиотека (ТОЛЬКО существующие файлы!)
add_library(paradox-dspirit
    src/dspirit.cpp
)

# Заголовочные файлы
target_include_directories(paradox-dspirit
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Псевдоним для удобства
add_library(paradox::dspirit ALIAS paradox-dspirit)

# ПРОСТОЙ пример для начала
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples/basic_usage.cpp)
    add_executable(example_basic examples/basic_usage.cpp)
    target_link_libraries(example_basic paradox::dspirit)
endif()

# Простые тесты (добавим позже)
option(BUILD_TESTS "Build tests" OFF)  # Сначала выключим

if(BUILD_TESTS)
    message(STATUS "Tests disabled for initial setup")
endif()

message(STATUS "Project configured successfully!")
message(STATUS "Source files found:")
file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h")
foreach(SOURCE ${SOURCES})
    message(STATUS "  ${SOURCE}")
endforeach()