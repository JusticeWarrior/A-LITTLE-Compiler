#!/bin/bash
make clean
make


if (( $# == 1 )); then
  RANGE=$1
else
  RANGE="1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21"
fi

echo -e CASE "\t" ACTUAL "\t" EXPECTED
for i in $RANGE; do
  TEST_OUT=$(cat "testcases/input/test${i}.micro" | micro | tail -n1);
  REAL_OUT=$(cat "testcases/output/test${i}.out");
  if [[ $TEST_OUT != $REAL_OUT ]] ; then
    COLOR="\033[0;31m"
  else
    COLOR=""
  fi
  echo -e "${COLOR}${i}" "\t" $TEST_OUT "\t" $REAL_OUT "\033[0m"

done
