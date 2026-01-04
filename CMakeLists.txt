cmake_minimum_required(VERSION 3.14)
project(paradox-dspirit VERSION 1.0.0 LANGUAGES CXX)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Для Windows
if(MSVC)
    add_compile_options(/W4 /MP /EHsc)
    add_definitions(-DNOMINMAX -D_CRT_SECURE_NO_WARNINGS)
    # Для DLL
    if(BUILD_SHARED_LIBS)
        add_definitions(-DPARADOX_DSPIRIT_EXPORTS)
    endif()
else()
    # Для Linux/macOS
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Основная библиотека
add_library(paradox-dspirit src/dspirit.cpp)

# Заголовочные файлы
target_include_directories(paradox-dspirit
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Тестовый пример
add_executable(test_app examples/test_example.cpp)
target_link_libraries(test_app paradox-dspirit)

# Информация
message(STATUS "========================================")
message(STATUS "Project: paradox-dspirit ${PROJECT_VERSION}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "========================================")