#!/bin/bash

n=$1

nbr="$(ls test/$n/input | wc -l)"

passed=0
failed=0

echo -e "\033[1;34m------------Test $n*$n------------\033[0m"
for i in $(seq $nbr)
do
    src="test/$n/input/test_$i.txt"
    ref="test/$n/ref/test_$i-ref.txt"
    ./a.out $src comp.txt
    if diff -b comp.txt $ref &>/dev/null; then
        echo -e "\t\033[1;32m$i : Test passed\033[0m"
        passed=$((passed+1))
    else
        echo -e "\t\033[1;31m$i : Test failed\033[0m"
        failed=$((failed+1))
    fi
done
echo -e "\n\033[1;34m------------Summary-------------\033[0m"
echo -e "\033[1;32m\tPassed $passed\033[0m"
echo -e "\033[1;31m\tFailed $failed\033[0m"