#!/bin/bash

echo 'echo he#llo; exit' | ../bin/rshell.out
echo 'ls -a; ls #-a; exit' | ../bin/rshell.out

