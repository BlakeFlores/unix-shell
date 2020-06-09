#!/bin/bash

echo 'wc -l < t1.txt; exit' | ../bin/rshell.out
echo 'sort < t1.txt; exit' | ../bin/rshell.out
