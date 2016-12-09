#!/bin/bash
make clean
make


if (( $# == 1 )); then
  RANGE=$1
else
  RANGE="1 5 6 7 8 9 11 13 14 16 18 19 20 21"
fi

echo -e RUNNING TEST
for i in $RANGE; do
  TEST_OUT=$(Micro "testcases2/input/test${i}.micro");
  REAL_OUT=$(cat "testcases2/output/test${i}.out");
  if ! cat testcases2/input/test${i}.micro | micro | cmp -s - testcases2/output/test${i}.out  ; then
    COLOR="\033[0;31m"
    echo -e $COLOR "${i}FAILED======================\033[0m"
    cat testcases2/input/test${i}.micro | micro | diff -y - testcases2/output/test${i}.out
  else
    COLOR=""
    echo "${i}PASSED============================"
    if valgrind --leak-check=yes micro < testcases2/input/test${i}.micro &> /dev/null ; then
      echo "VALGRIND PASSED"
    else
      echo "VALGRIND FAILED OH NO"
    fi
  fi

done
