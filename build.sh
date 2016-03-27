#!/bin/bash

##
# Compile sources from /src/main to /dist/main
# -I Link project folders to #include
# -lm Link math library to output
#
# gcc --version
# gcc (GCC) 4.9.2 20150212 (Red Hat 4.9.2-6)
##

gcc -o dist/main \
    -I ./src/ \
    -I ./src/h/ \
    -I ./src/processes_handlers/ \
    -I ./src/memory_management/ \
    -I ./src/scheduling/ \
    src/main.c -lm
