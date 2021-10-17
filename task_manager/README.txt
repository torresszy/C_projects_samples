README file for: Task manager

Note: src directory is not included due to privacy reason

Makefile: file to be used with make.  Run:
  make test_task_manager - to compile your code and generate an executable for the automated test code
  make student_test_task_manager - to compile your code and generate an executable for your tests
  make all - to do both
  make clean - remove generated files
  make gen_score - generate your score on the automated tests.

include: a directory for the C header files
  task_manager.h - the include file for the task manager
  task_manager.h - the include file for the scheduler
  util.h - the include file for our test utility functions (you will not use these functions)
  
bin: a subdirectory that will be used to hold the binary executables

tests: a directory for the automated test files
  test_task_manager.c - the Criterion tests for the programming assignment
  grader.py - a Python file used to compute the Completeness score.
  util.c - helper functions used by the test code.

README.txt: this file
