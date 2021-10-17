README file for: A Game of Chance

Note: src directory is not included due to privacy reason

Makefile: file to be used with make.  Run:
  make test_betting - to compile your code and generate an executable for the automated test code
  make student_test_betting - to compile your code and generate an executable for your tests
  make all - to do both
  make clean - remove generated files
  make gen_score - generate your score on the automated tests.

include: a directory for the C header files
  betting.h - the include file game of chance simulation code
  util.h - the include file for our utility functions: flip_coin, flip_only, betting_strategies_to_str.
  
bin: a subdirectory that will be used to hold the binary executables

tests - a directory for the automated test files
  test_betting.c - the Criterion tests for the short exercises
  grader.py - a Python file used to compute short exercise scores.

README.txt: this file
