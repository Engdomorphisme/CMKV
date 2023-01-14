#!/bin/bash

size=$1
file=$2
number="$(ls $size/ref | wc -l)"
number=$((number+1))

cp -r $file $size/ref/test_$number-ref.txt

./a.out $file "test_$number.txt"

mv test_$number.txt $size/input/