#!/bin/bash

echo 'test -e ../tests; exit' | ../bin/rshell.out
echo '[ -e ../tests ]; exit' | ../bin/rshell.out
echo 'test ../tests; exit' | ../bin/rshell.out
echo 'test -f ../tests/test_test.sh; exit' | ../bin/rshell.out
echo 'test -d ../tests; exit' | ../bin/rshell.out
echo 'test -f ../tests; exit' | ../bin/rshell.out
echo 'test -d ../tests/test_test.sh; exit' | ../bin/rshell.out
echo 'test -e ../tests && echo “path exists”; exit' | ../bin/rshell.out
echo '[ -e ../tests ] && echo “path exists2”; exit' | ../bin/rshell.out
echo '[ -e ../tests/test_test.sh ] && echo “file exist”; exit' | ../bin/rshell.out
echo '[ -e test/file/path ] || echo “path does not exists"; exit' | ../bin/rshell.out
