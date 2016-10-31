#!/bin/bash
make clean
make

exit_code=0

run_test() {
  echo "RUNNING FILE ${1}.micro =================="
  cat testcases4/input/$1.micro | micro > test.out
  testcases4/tiny test.out | head -n1 > test.result
  rm test.out
  if testcases4/tiny testcases4/output/$1.out | head -n1 | diff - test.result ; then
    echo PASSED
    rm test.result
  else
    rm test.result
    echo -e "\033[0;31mFAILED\033[0m"
    exit_code=1
  fi
}

run_test step4_testcase2
run_test step4_testcase
run_test test_adv
run_test test_dowhile
run_test test_if
