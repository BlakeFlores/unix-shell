#!/bin/bash'
echo 'cp 2.txt 3.txt; exit' | ../bin/rshell.out
echo 'echo “zebra fruit” >> 3.txt; exit' | ../bin/rshell.out

