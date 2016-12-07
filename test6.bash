#!/bin/bash
#make clean
#make compiler

exit_code=0

run_test() {
  echo "RUNNING FILE ${1}.micro =================="
  Micro testcases6/inputs/${1}.micro > test.out
  cat testcases6/inputs/${1}.input | testcases6/tiny4R test.out | head -n1 > test.result
  rm test.out
  if cat testcases6/outputs/${1}.tinyout | head -n1 | diff - test.result ; then
    echo PASSED
    rm test.result
  else
    rm test.result
    echo -e "\033[0;31mFAILED\033[0m"
    exit_code=1
  fi
}

run_test fma
run_test factorial2
run_test fibonacci2
run_test step4_testcase2
run_test step4_testcase3
run_test test_adv
run_test test_if
run_test test_dowhile
