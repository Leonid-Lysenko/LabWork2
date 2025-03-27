#!/bin/bash

echo "=== Card Heroes Battle Build Script ==="

# Создаем директории сборки
mkdir -p build
cd build

# Конфигурация и сборка с помощью CMake
cmake ..
make -j$(nproc)

# Запуск тестов
if [ "$1" == "--test" ]; then
    ctest --output-on-failure
fi

# Генерация документации
if [ "$1" == "--docs" ]; then
    make docs
fi 