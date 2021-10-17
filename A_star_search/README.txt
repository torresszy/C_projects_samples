README file for A* Search

Note: src directory is not included due to privacy reason

Makefile: file to be used with make.  Run:
  make test_a_star - to compile your code and generate an executable for the automated test code
  make student_test_a_star - to compile your code and generate an executable for your tests
  make all - to do both
  make clean - remove generated files
  make gen_score - generate your score on the automated tests.

include: a directory for the C header files
  a_star.h - the include file for A* search
  util.h - the include file for our utility functions for sets and priority queues
  
bin: a subdirectory that will be used to hold the binary executables

tests: a directory for the automated test files
  test_a_star.c - the Criterion tests for the programming assignment
  grader.py - a Python file used to compute the Completeness score.

README.txt: this file
