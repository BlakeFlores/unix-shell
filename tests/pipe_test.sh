#!/bin/bash
echo 'echo "dog" | sed "s/dog/bird/"; exit' | ../bin/rshell.out
echo 'ls | cat; exit' | ../bin/rshell.out
echo 'cat *.txt | sort | uniq > result-file; exit' | ../bin/rshell.out
