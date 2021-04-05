CS 152, Winter 2021
README file for PA #1: A Game of Chance

Makefile: file to be used with make.  Run:
  make test_betting - to compile your code and generate an executable for the automated test code
  make student_test_betting - to compile your code and generate an executable for your tests
  make all - to do both
  make clean - remove generated files
  make gen_score - generate your score on the automated tests.

src: a subdirectory for the C source files
  betting.c - the C file for this programming assignment.  You will do most of your work in this file.
  student_test_betting.c - a C file that you can use to test your code by hand.  Add calls
    to your functions to the main function.  Add test helper functions as needed.
  util.c - a C file that contains utility code for flipping coins, etc.

include: a directory for the C header files
  betting.h - the include file game of chance simulation code
  util.h - the include file for our utility functions: flip_coin, flip_only, betting_strategies_to_str.
  
bin: a subdirectory that will be used to hold the binary executables

tests - a directory for the automated test files
  test_betting.c - the Criterion tests for the short exercises
  grader.py - a Python file used to compute short exercise scores.

README.txt: this file
