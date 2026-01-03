# src/CMakeLists.txt

# Собираем библиотеку spirit
add_library(spirit_lib STATIC
    spirit_double.cpp
    spirit_float.cpp
)

# Для Windows нужно явно экспортировать символы
if(WIN32)
    set_target_properties(spirit_lib PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
endif()

# Публичные заголовочные файлы
target_include_directories(spirit_lib
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

# Специфичные настройки для Windows
if(MSVC)
    target_compile_definitions(spirit_lib PRIVATE _USE_MATH_DEFINES)
endif()

# Опционально: библиотека для нейросети
add_library(spirit_neural STATIC
    simple_neural.cpp
)

target_include_directories(spirit_neural
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(spirit_neural PUBLIC spirit_lib)