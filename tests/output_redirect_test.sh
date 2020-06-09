#!/bin/bash
echo '(echo apples; echo oranges; echo bananas; echo tangelos; echo raspberry; echo blueberry) > unsorted_list.txt; exit'  | ../bin/rshell.out
echo 'sort < unsorted_list.txt > sorted_list.txt; exit' | ../bin/rshell.out
echo 'ls -lR > dir-tree.list; exit' | ../bin/rshell.out
