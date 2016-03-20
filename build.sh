#!/bin/bash
gcc -o dist/main \
    -I ./src/ \
    -I ./src/h/ \
    -I ./src/processes_handlers/ \
    -I ./src/memory_management/ \
    -I ./src/scheduling/ \
    src/main.c
