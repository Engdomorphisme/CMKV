#!/bin/bash

n=$1

nbr="$(ls test/$n/input | wc -l)"

passed=0
failed=0

echo -e "\e[1;34m------------Test $n*$n------------\e[0m"
for i in $(seq $nbr)
do
    src="test/$n/input/test_$i.txt"
    ref="test/$n/ref/test_$i-ref.txt"
    ./a.out $src comp.txt
    if diff -b comp.txt $ref &>/dev/null; then
        echo -e "\t\e[1;32m$i : Test passed\e[0m"
        passed=$((passed+1))
    else
        echo -e "\t\e[1;31m$i : Test failed\e[0m"
        failed=$((failed+1))
    fi
done
echo -e "\n\e[1;34m------------Summary-------------\e[0m"
echo -e "\e[1;32m\tPassed $passed\e[0m"
echo -e "\e[1;31m\tFailed $failed\e[0m"