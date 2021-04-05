CS 152, Winter 2021
README file for PA #2: Image Processing

Makefile: file to be used with make.  Run:
  make test_images - to compile your code and generate an executable for the automated test code
  make student_test_images - to compile your code and generate an executable for your tests
  make all - to do both
  make clean - remove generated files
  make gen_score - generate your score on the automated tests.

src: a subdirectory for the C source files
  images.c - the C file for this programming assignment.  You will do most of your work in this file.
  student_test_images.c - a C file that you can use to test your code by hand.  Add calls
    to your functions to the main function.  Add test helper functions as needed.
  util.c - a C file that contains utility code for reading and writing PPM files.

include: a directory for the C header files
  images.h - the include file for image processing code
  util.h - the include file for our utility functions: read_ppm, write_ppm. 
  
bin: a subdirectory that will be used to hold the binary executables

tests: a directory for the automated test files
  test_images.c - the Criterion tests for the programming assignment
  grader.py - a Python file used to compute the Completeness score.
  test-images - a directory of images used in Criterion tests

images: a directory of PPM images for student testing

README.txt: this file
