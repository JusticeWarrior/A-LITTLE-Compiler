#!/bin/bash
make clean
make

exit_code=0

run_test() {
  echo "RUNNING FILE ${1}.micro =================="
  Micro testcases3/input/$1.micro > test.out
  testcases3/tiny test.out | head -n1 > test.result
  rm test.out
  if testcases3/tiny testcases3/output/$1.out | head -n1 | diff - test.result ; then
    echo PASSED
    rm test.result
  else
    rm test.result
    echo "\033[0;31mFAILED\033[0m"
    exit_code=1
  fi
}

run_test test_expr
run_test step4_testcase3
