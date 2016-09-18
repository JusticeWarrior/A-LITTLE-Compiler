#!/bin/bash
make clean
make
for i in {1..20}; do
  TEST_OUT=$(cat "testcases/input/test${i}.micro" | micro);
  echo $TEST_OUT

done
