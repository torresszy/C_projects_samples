OBJECTS = 
CFLAGS = -g -Wall --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: student_tests automated_tests

student_tests: student_test_task student_test_task_manager student_test_scheduler

automated_tests: test_core_simulator

%.o: %.c
	$(CC) -c $(CFLAGS) $?  -I $(INCLUDES)

student_test_task: $(SOURCE)/task.c $(SOURCE)/student_test_task.c
	$(CC) $(CFLAGS) $? -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

student_test_task_manager: $(SOURCE)/task.c $(SOURCE)/student_test_task_manager.c $(SOURCE)/task_manager.c
	$(CC) $(CFLAGS) $? -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

student_test_scheduler: $(SOURCE)/task.c $(SOURCE)/student_test_scheduler.c $(SOURCE)/task_manager.c $(SOURCE)/scheduler.c
	$(CC) $(CFLAGS) $? -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

test_core_simulator: $(TESTS)/test_core_simulator.c $(SOURCE)/scheduler.c $(SOURCE)/task.c $(SOURCE)/task_manager.c  $(TESTS)/util.c $(TESTS)/test_helpers.c
	$(CC) $(CFLAGS) $?  -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

gen_score: test_core_simulator
	-bin/test_core_simulator --json > results.log 2> results.json
	python3 tests/grader.py

clean:
	rm -f results.json results.log
	rm -rf $(BIN)/*.dSYM
	rm -f $(BIN)/student_* $(BIN)/test_*
	rm -rf *~ */*~
