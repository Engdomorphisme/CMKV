#!/bin/bash

./test_given.sh

for n in {2..6}
do
    ./test.sh $n
done