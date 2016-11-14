#!/bin/bash
make clean
make compiler

exit_code=0

run_test() {
  echo "RUNNING FILE ${1}.micro =================="
  Micro testcases5/input/${1}.micro > test.out
  cat testcases5/input/${1}.input | testcases5/tiny test.out | head -n1 > test.result
  rm test.out
  if cat testcases5/output/${1}.tinyout | head -n1 | diff - test.result ; then
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
