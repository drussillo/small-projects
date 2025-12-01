#!/usr/bin/env bash
clear
gcc -o build/connect4 -Iinclude/ src/*.c
./build/connect4
