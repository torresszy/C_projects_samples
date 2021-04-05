OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: student_test_betting test_betting

student_test_betting: $(SOURCE)/betting.c $(SOURCE)/student_test_betting.c $(SOURCE)/util.c
	$(CC) $(CFLAGS) $? -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

test_betting: $(TESTS)/test_betting.c $(SOURCE)/betting.c $(SOURCE)/util.c
	$(CC) $(CFLAGS) $?  -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

gen_score: test_betting
	-bin/test_betting --json > results.log 2> results.json
	python3 tests/grader.py

clean:
	rm -f results.json results.log
	rm -f $(BIN)/student_test_betting $(BIN)/test_betting
	rm -rf $(BIN)/*.dSYM
	rm -rf *~ */*~
