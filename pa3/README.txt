CS 152, Winter 2021
README file for PA #3: Task manager

Makefile: file to be used with make.  Run:
  make test_task_manager - to compile your code and generate an executable for the automated test code
  make student_test_task_manager - to compile your code and generate an executable for your tests
  make all - to do both
  make clean - remove generated files
  make gen_score - generate your score on the automated tests.

src: a subdirectory for the C source files
  task_manager.c - the C file for Task 1.  You will do your work for Task 1 in this file
  scheduler.c - the C file for Task 2.  You will do your work for Task 1 in this file
  student_test_task_manager.c - a C file that you can use to test your code by hand.  Add calls
    to your functions to the main function.  Add test helper functions as needed.

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
