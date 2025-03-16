@echo off
echo === Простая сборка Card Heroes Battle ===

REM Создание директорий
if not exist build\bin mkdir build\bin

REM Компиляция исходных файлов с Visual C++
echo Компиляция исходников...
set INCLUDE_DIR=include
set SRC_DIR=src
set OUT_DIR=build\bin

REM Сначала компилируем библиотеку
cl /c /EHsc /std:c++17 /I%INCLUDE_DIR% %SRC_DIR%\*.cpp /Fo%OUT_DIR%\
if %ERRORLEVEL% NEQ 0 (
    echo !!! Ошибка при компиляции библиотеки !!!
    exit /b %ERRORLEVEL%
)

REM Затем компилируем основной файл и создаем исполняемый файл
cl /EHsc /std:c++17 /I%INCLUDE_DIR% %SRC_DIR%\main.cpp %OUT_DIR%\*.obj /Fe%OUT_DIR%\CardHeroesBattle.exe
if %ERRORLEVEL% NEQ 0 (
    echo !!! Ошибка при компиляции исполняемого файла !!!
    exit /b %ERRORLEVEL%
)

echo === Проект успешно скомпилирован ===
echo Исполняемый файл находится в директории %OUT_DIR%\CardHeroesBattle.exe