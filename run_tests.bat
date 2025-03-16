@echo off
echo ========================================
echo === Запуск тестов для Card Heroes Battle ===
echo ========================================

REM Настройка переменных проекта
set INCLUDE_DIR=include
set SRC_DIR=src
set TEST_DIR=tests
set BUILD_DIR=build
set TEST_BIN_DIR=%BUILD_DIR%\tests

REM Создание директорий
if not exist %TEST_BIN_DIR% mkdir %TEST_BIN_DIR%

REM Компиляция тестовых файлов
echo Компиляция тестовых файлов...
cl /EHsc /std:c++17 /I%INCLUDE_DIR% %TEST_DIR%\*.cpp /Fe%TEST_BIN_DIR%\run_tests.exe

if %ERRORLEVEL% NEQ 0 (
    echo !!! Ошибка при компиляции тестов !!!
    exit /b %ERRORLEVEL%
)

REM Запуск тестов
echo Запуск тестов...
%TEST_BIN_DIR%\run_tests.exe

if %ERRORLEVEL% NEQ 0 (
    echo !!! Тесты не пройдены !!!
    exit /b %ERRORLEVEL%
)

echo ============================
echo === Все тесты пройдены! ===
echo ============================