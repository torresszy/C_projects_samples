OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: student_test_images test_images

student_test_images: $(SOURCE)/images.c $(SOURCE)/student_test_images.c $(SOURCE)/util.c
	$(CC) $(CFLAGS) $? -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

test_images: $(TESTS)/test_images.c $(SOURCE)/images.c $(SOURCE)/util.c
	$(CC) $(CFLAGS) $?  -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

gen_score: test_images
	-bin/test_images --json > results.log 2> results.json
	python3 tests/grader.py

clean:
	rm -f results.json results.log
	rm -f $(BIN)/student_test_images $(BIN)/test_images
	rm -rf $(BIN)/*.dSYM
	rm -rf *~ */*~
