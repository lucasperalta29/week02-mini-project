#!/usr/bin/env bash
set -eu
mkdir -p build
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o build/app
for i in 1 2 3 4; do
    ./build/app < tests/input$i.txt > build/actual$i.txt
    diff -u tests/expected$i.txt build/actual$i.txt
done
echo "All acceptance tests passed"
