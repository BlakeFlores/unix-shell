#!/bin/bash

echo 'echo Hello && echo World; echo Good && echo Night; exit' | ../bin/rshell.out
echo 'ls -a; echo hello && mkdir test || echo world; git status; exit' | ../bin/rshell.out
