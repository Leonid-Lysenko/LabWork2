@echo off
echo ========================================
echo === Card Heroes Battle CI/CD Pipeline ===
echo ========================================

REM Настройка переменных проекта
set PROJECT_NAME=CardHeroesBattle
set INCLUDE_DIR=include
set SRC_DIR=src
set BUILD_DIR=build
set DOC_DIR=docs
set BIN_DIR=%BUILD_DIR%\bin
set OBJ_DIR=%BUILD_DIR%\obj

REM Создание директорий
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if not exist %BIN_DIR% mkdir %BIN_DIR%
if not exist %OBJ_DIR% mkdir %OBJ_DIR%
if not exist %DOC_DIR%\html mkdir %DOC_DIR%\html

REM Очистка старых файлов
echo Очистка старых файлов...
del /Q %BIN_DIR%\*.exe 2>nul
del /Q %OBJ_DIR%\*.obj 2>nul

REM Компиляция исходных файлов
echo Компиляция исходных файлов...
cl /c /EHsc /std:c++17 /I%INCLUDE_DIR% /Fo%OBJ_DIR%\ %SRC_DIR%\card.cpp %SRC_DIR%\game_mode.cpp

if %ERRORLEVEL% NEQ 0 (
    echo !!! Ошибка при компиляции библиотечных файлов !!!
    exit /b %ERRORLEVEL%
)

REM Компиляция главного файла
echo Компиляция главного файла...
cl /EHsc /std:c++17 /I%INCLUDE_DIR% %SRC_DIR%\main.cpp %OBJ_DIR%\*.obj /Fe%BIN_DIR%\%PROJECT_NAME%.exe

if %ERRORLEVEL% NEQ 0 (
    echo !!! Ошибка при компиляции главного файла !!!
    exit /b %ERRORLEVEL%
)

REM Генерация документации
echo Генерация документации...
call generate_docs.bat

REM Запуск тестов (если есть)
if exist run_tests.bat (
    echo Запуск тестов...
    call run_tests.bat
)

echo =======================================
echo === Сборка успешно завершена! ===
echo =======================================
echo Исполняемый файл: %BIN_DIR%\%PROJECT_NAME%.exe
echo Документация: %DOC_DIR%\html\index.html