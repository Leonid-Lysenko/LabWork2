cmake_minimum_required(VERSION 3.14)
project(CardHeroesBattle VERSION 1.0)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Тесты
if(BUILD_TESTS)
    find_package(GTest)
    if(GTEST_FOUND)
        file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
        add_executable(run_tests ${TEST_SOURCES})
        target_link_libraries(run_tests PRIVATE 
            ${PROJECT_NAME}_lib
            GTest::GTest 
            GTest::Main
        )
        
        add_test(NAME unit_tests COMMAND run_tests)
        message(STATUS "GTest found, tests will be built")
    else()
        message(STATUS "GTest not found, tests will be skipped")
    endif()
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
