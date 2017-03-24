#!/bin/bash
echo "Compiling..."
gcc *.c -o main -lwiringPi -lwiringPiDev
echo "Compile completed !"
