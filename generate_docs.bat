@echo off
echo === Генерация документации для Card Heroes Battle ===

REM Создание Doxyfile
doxygen -g Doxyfile.temp

REM Настройка параметров Doxygen
echo PROJECT_NAME = "Card Heroes Battle" > Doxyfile
echo PROJECT_NUMBER = 1.0 >> Doxyfile
echo OUTPUT_DIRECTORY = docs/html >> Doxyfile
echo INPUT = include src >> Doxyfile
echo RECURSIVE = YES >> Doxyfile
echo EXTRACT_ALL = YES >> Doxyfile
echo EXTRACT_PRIVATE = YES >> Doxyfile
echo EXTRACT_STATIC = YES >> Doxyfile
echo HAVE_DOT = NO >> Doxyfile
echo CLASS_GRAPH = YES >> Doxyfile
echo GENERATE_LATEX = NO >> Doxyfile

REM Запуск Doxygen
echo Генерация документации...
doxygen Doxyfile

REM Проверка успешности
if %ERRORLEVEL% NEQ 0 (
    echo !!! Ошибка при генерации документации !!!
    exit /b %ERRORLEVEL%
) else (
    echo === Документация успешно сгенерирована ===
    echo Документация находится в директории docs/html
)

REM Открытие документации в браузере
start docs\html\index.html