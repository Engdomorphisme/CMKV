#!/bin/bash

passed=0
failed=0

for i in {2..6}
do
echo -e "\e[1;34m------------Test $i*$i------------\e[0m"
for j in {1..9}
do
    src="test/given/input/s$i-0$j.txt"
    ref="test/given/ref/s$i-0$j-ref.txt"
    ./a.out $src comp.txt
    if diff -b comp.txt $ref &>/dev/null; then
        echo -e "\t\e[1;32m$j : Test passed\e[0m"
        passed=$((passed+1))
    else
        echo -e "\t\e[1;31m$j : Test failed\e[0m"
        failed=$((failed+1))
    fi
done
done 
echo -e "\n\e[1;34m------------Summary-------------\e[0m"
echo -e "\e[1;32m\tPassed $passed\e[0m"
echo -e "\e[1;31m\tFailed $failed\e[0m"

rm comp.txt