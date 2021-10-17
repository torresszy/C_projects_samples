OBJECTS = 
CFLAGS = -g -Wall --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: student_test_task_manager test_task_manager

%.o: %.c
	$(CC) -c $(CFLAGS) $?  -I $(INCLUDES)

student_test_task_manager: $(SOURCE)/task_manager.c $(SOURCE)/student_test_task_manager.c $(SOURCE)/scheduler.c
	$(CC) $(CFLAGS) $? -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

test_task_manager: $(TESTS)/test_task_manager.c $(SOURCE)/task_manager.c $(SOURCE)/scheduler.c $(TESTS)/util.c
	$(CC) $(CFLAGS) $?  -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

gen_score: test_task_manager
	-bin/test_task_manager --json > results.log 2> results.json
	python3 tests/grader.py

clean:
	rm -f results.json results.log
	rm -f $(BIN)/student_test_task_manager $(BIN)/test_task_manager
	rm -rf $(BIN)/*.dSYM
	rm -rf *~ */*~
