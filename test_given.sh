#!/bin/bash

passed=0
failed=0

for i in {2..6}
do
  #\033[0;31m
echo -e "\033[1;34m------------Test $i*$i------------\033[0m"
for j in {1..9}
do
    src="test/given/input/s$i-0$j.txt"
    ref="test/given/ref/s$i-0$j-ref.txt"
    ./a.out $src comp.txt
    if diff -b comp.txt $ref &>/dev/null; then
        echo -e "\t\033[1;32m$j : Test passed\033[0m"
        passed=$((passed+1))
    else
        echo -e "\t\033[1;31m$j : Test failed\033[0m"
        failed=$((failed+1))
    fi
done
done 

echo -e "\n\033[1;34m------------Summary-------------\033[0m"
echo -e "\033[1;32m\tPassed $passed\033[0m"
echo -e "\033[1;31m\tFailed $failed\033[0m"

rm comp.txt