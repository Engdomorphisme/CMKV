#!/bin/bash

size=$1
number="$(ls $size/ref | wc -l)"
number=$((number+1))
for i in $(seq $number 100)
do
  ./create_test $size board.txt


  cp -r board.txt $size/ref/test_$i-ref.txt

  ./swap_board board.txt "test_$i.txt"

  mv test_$i.txt $size/input/
done