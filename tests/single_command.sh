#!/bin/bash

echo 'echo test; exit' | ../bin/rshell.out
echo 'echo echo echo; ls; exit' | ../bin/rshell.out
echo 'mkdir test; ls -a; exit' | ../bin/rshell.out
