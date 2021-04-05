CS 152, Winter 2021
README file for PA #4: Trie

Makefile: file to be used with make.  Run:
  make test_trie - to compile your code and generate an executable for the automated test code
  make student_test_trie - to compile your code and generate an executable for your tests
  make all - to do both
  make clean - remove generated files
  make gen_score - generate your score on the automated tests.

src: a subdirectory for the C source files
  trie.c - the C file for this programming assignment.  You will do most of your work in this file.
  student_test_trie.c - a C file that you can use to test your code by hand.  Add calls
    to your functions to the main function.  Add test helper functions as needed.

include: a directory for the C header files
  trie.h - the include file for the trie
  
bin: a subdirectory that will be used to hold the binary executables

tests: a directory for the automated test files
  test_trie.c - the Criterion tests for the programming assignment
  grader.py - a Python file used to compute the Completeness score.

README.txt: this file
