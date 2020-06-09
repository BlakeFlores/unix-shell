#!/bin/bash

echo 'echo A && echo B || echo C && echo D; exit' | ../bin/rshell.out
echo '(echo A && echo B) || (echo C && echo D); exit' | ../bin/rshell.out
echo '(((echo multiple paren))); exit' | ../bin/rshell.out
echo 'true && (echo Well && echo Done); exit' | ../bin/rshell.out
echo 'false && (echo Hello && echo World); exit' | ../bin/rshell.out
echo 'true || (echo Shouldnt && echo Display); exit' | ../bin/rshell.out
echo 'false || (echo Should && echo Display); exit' | ../bin/rshell.out
