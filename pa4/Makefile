OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: student_test_trie test_trie

student_test_trie: $(SOURCE)/trie.c $(SOURCE)/student_test_trie.c
	$(CC) $(CFLAGS) $? -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

test_trie: $(TESTS)/test_trie.c $(SOURCE)/trie.c
	$(CC) $(CFLAGS) $?  -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

gen_score: test_trie
	-bin/test_trie --json > results.log 2> results.json
	python3 tests/grader.py

clean:
	rm -f results.json results.log
	rm -f $(BIN)/student_test_trie $(BIN)/test_trie
	rm -rf $(BIN)/*.dSYM
	rm -rf *~ */*~
