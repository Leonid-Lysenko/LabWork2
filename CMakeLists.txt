cmake_minimum_required(VERSION 3.14)
project(CardHeroesBattle VERSION 1.0)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем поддержку компиляторов для разных платформ
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Опции сборки
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" ON)

# Исходные файлы
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "include/*.h"
)

# Создание библиотеки
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

# Добавляем поддержку покрытия кода для Linux
if(UNIX)
    target_compile_options(${PROJECT_NAME}_lib PRIVATE --coverage)
    target_link_libraries(${PROJECT_NAME}_lib PRIVATE gcov)
endif()

# Добавляем поддержку sanitizers для отладки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(UNIX)
        target_compile_options(${PROJECT_NAME}_lib PRIVATE -fsanitize=address,undefined)
        target_link_options(${PROJECT_NAME}_lib PRIVATE -fsanitize=address,undefined)
    endif()
endif()

# Тесты
# В разделе тестов замените на:
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    
    # Создаем отдельный тестовый исполняемый файл
    add_executable(game_tests
        tests/player_test.cpp
        tests/card_test.cpp
        tests/game_mode_test.cpp
        tests/effect_test.cpp
        tests/test_main.cpp  # Новый файл с точкой входа
    )
    
    target_link_libraries(game_tests PRIVATE
        ${PROJECT_NAME}_lib
        GTest::GTest
        GTest::Main
    )
    
    add_test(NAME game_unit_tests COMMAND game_tests)
endif()

# Документация
if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        
        add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    endif()
endif()
