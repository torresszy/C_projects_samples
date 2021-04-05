/* CMSC 15200, Winter 2021
 *  PA #3 Task Manager: automated test code
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

#include "task_manager.h"
#include "scheduler.h"
#include "util.h"

/* Replicate the hidden types here to allow the test code
 * to check the implementation.
 */
 
/* Doubly-linked list (DLL) of tasks */
typedef struct dll_node dll_t;
struct dll_node {
    int tid;      // task identifier
    int priority; // task priority
    int run_time; // task run-time
    dll_t *next;  // next node in the list
    dll_t *prev;  // previous node in the list
};

/* Structure definition for the task manager */
struct task_manager {
    dll_t *task_list;
    int max_priority;
    int next_tid;
};

#define BASIC_MAX_PRIORITY 2

void verify_tm(task_manager_t *tm, int max_priority, int num_tasks,
               int tids[], int priorities[], int running_times[],
               char *test_desc, char *test_str)
{
    cr_assert_neq(tm, NULL, "Got a NULL task manager\n");

    check_int(tm->max_priority, max_priority, "maximum priority",
              test_desc, test_str);
    char err_msg[ERR_MSG_LEN];

    dll_t *tl = tm->task_list;
    cr_assert_neq(tl, NULL, "Got a unexpected NULL pointer\n");
    dll_t *curr = tl->next;
    dll_t *last = curr;

    for (int i=0; i < num_tasks; i++) {
        cr_assert_neq(curr, NULL, "Got a unexpected NULL pointer\n");
        snprintf(err_msg, ERR_MSG_LEN-1,
                 ("Failed %s\n  Encountered Bad Task at list element %d\n  "
                  "  Actual Task: (%d, %d, %d)\n"
                  "  Expected Task: (%d, %d, %d)\n"
                  "Command to rerun this test: "
                  "bin/test_task_manager --filter %s\n"),
                 test_desc, i, curr->tid, curr->priority, curr->run_time,
                 tids[i], priorities[i], running_times[i],
                 test_str);
        cr_assert_eq(curr->tid, tids[i], " \n%s", err_msg);
        cr_assert_eq(curr->priority, priorities[i], " \n%s", err_msg);
        cr_assert_eq(curr->run_time, running_times[i], " \n%s", err_msg);

        last = curr;
        curr = curr->next;        
    }

    cr_assert_neq(curr, NULL, "Got a unexpected NULL pointer\n");
    snprintf(err_msg, ERR_MSG_LEN-1,
             ("Failed %s\n  Extra task or bad next pointer"
              " at the end of the list\n"
              "Command to rerun this test: "
              "bin/test_task_manager --filter %s\n"),
             test_desc, test_str);
    cr_assert_eq(curr, tm->task_list, " \n%s", err_msg);

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("Failed %s\n  Bad prev pointer in dummy node"
              " at the end of the list\n"
              "Command to rerun this test: "
              "bin/test_task_manager --filter %s\n"),
             test_desc, test_str);
    cr_assert_eq(tm->task_list->prev, last, " \n%s", err_msg);


}

void verify_and_free_empty_tm(task_manager_t *tm, int max_priority, 
                              char *test_desc, char *test_str) 
{
    verify_tm(tm, max_priority, 0, NULL, NULL, NULL,
              test_desc, test_str);
    tm_free(tm);
}

task_manager_t *mk_sample_tm(int max_priority, int num_tasks,
                             int priorities[], int runtimes[], int tids[],
                             char *test_desc, char *test_str)
{
    task_manager_t *tm = tm_create(max_priority);

    for (int i = 0; i < num_tasks; i++) {
        tids[i] = tm_add_task(tm, priorities[i], runtimes[i]);
    }

    verify_tm(tm, max_priority, num_tasks, 
              tids, priorities, runtimes,
              test_desc, test_str);

    return tm;
}



task_manager_t *mk_zero(char *test_str)
{
    int max_priority = BASIC_MAX_PRIORITY;
    task_manager_t *tm = mk_sample_tm(max_priority, 0, NULL, NULL, NULL,
                                      "Zero tasks", test_str);
    return tm;
}

task_manager_t *mk_one(char *test_str)
{
    int max_priority = BASIC_MAX_PRIORITY;
    int num_tasks = 1;
    int tids[num_tasks];
    int priorities[] = {2};
    int runtimes[] = {10};

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "One task", test_str);
    return tm;
}

char *bool_str(bool b) {
    return b ? "true" : "false";
}

/***************************************************************/
TestSuite(tm_add_task, .timeout=60);

Test(tm_add_task, testA) 
{
    task_manager_t *tm = mk_one("tm_add_task/testA");
    tm_free(tm);
}

Test(tm_add_task, testB) 
{
    int max_priority = 5;
    int num_tasks = 2;
    int tids[num_tasks];
    int priorities[] = {2, 0};
    int runtimes[] = {20, 10};
    char *test_desc = "Add task: add two elements to an empty list";
    char *test_str = "tm_add_task/testB";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      test_desc, test_str);
    tm_free(tm);                                      
}

Test(tm_add_task, testC) 
{
    int max_priority = 5;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 3, 1, 4, 1, 5, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    char *test_desc = "Add task: add ten elements to an empty list";
    char *test_str = "tm_add_task/testC";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      test_desc, test_str);
    tm_free(tm);                                      
}


/***************************************************************/
TestSuite(tm_is_empty, .timeout=60);

void tm_is_empty_helper(task_manager_t *tm, 
                        bool expected, 
                        char *test_desc,
                        char *test_str)
{
    bool actual = tm_is_empty(tm);
    check_bool(actual, expected, "return value", test_desc, test_str);
    tm_free(tm);
}

Test(tm_is_empty, testA) 
{
    char *test_str = "tm_is_empty/testA";
    task_manager_t *tm = mk_zero(test_str);
    tm_is_empty_helper(tm, true, "tm_is_empty:No tasks", test_str);
}

Test(tm_is_empty, testB) 
{
    char *test_str = "tm_is_empty/testB";
    task_manager_t *tm = mk_one(test_str);
    tm_is_empty_helper(tm, false, "tm_is_empty: One task", test_str);
}

Test(tm_is_empty, testC) 
{
    int max_priority = 2;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 0, 1, 0, 1, 0, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    char *test_str = "tm_is_empty/testC";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Constructing a ten element list",
                                      test_str);                                    

    tm_is_empty_helper(tm, false, "tm_is_empty: Many tasks", test_str);
}

/***************************************************************/
TestSuite(tm_get_num_tasks, .timeout=60);

void tm_get_num_tasks_helper(task_manager_t *tm, 
                             int expected, 
                             char *test_desc,
                             char *test_str)
{
    int actual = tm_get_num_tasks(tm);
    check_int(actual, expected, "number of tasks", test_desc, test_str);
    tm_free(tm);
}

Test(tm_get_num_tasks, testA) 
{
    char *test_str = "get_num_tasks/testA";
    task_manager_t *tm = mk_zero(test_str);
    tm_get_num_tasks_helper(tm, 0, "tm_get_num_tasks: No tasks", test_str);
}

Test(tm_get_num_tasks, testB) 
{
    char *test_str = "get_num_tasks/testB";
    task_manager_t *tm = mk_one(test_str);
    tm_get_num_tasks_helper(tm, 1, "tm_get_num_tasks: One task", test_str);
}

Test(tm_get_num_tasks, testC) 
{
    int max_priority = 2;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 0, 1, 0, 1, 0, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    char *test_str = "get_num_tasks/testC";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Constructing a ten element list", 
                                      test_str);
    tm_get_num_tasks_helper(tm, num_tasks, "tm_get_num_tasks: Many tasks", 
                            test_str);
}

/***************************************************************/
TestSuite(tm_get_max_priority, .timeout=60);

void tm_get_max_priority_helper(task_manager_t *tm, 
                                int expected, 
                                char *test_desc,
                                char *test_str)
{
    int actual = tm_get_max_priority(tm);
    check_int(actual, expected, "maximum priority", test_desc, test_str);
    tm_free(tm);
}

Test(tm_get_max_priority, testA) 
{
    char *test_desc = "tm_get_max_priority: No tasks";
    char *test_str = "get_max_priority/testA";
    task_manager_t *tm = mk_zero(test_str);
    tm_get_max_priority_helper(tm, BASIC_MAX_PRIORITY, 
                               test_desc, test_str);
}

Test(tm_get_max_priority, testB) 
{
    int max_priority = 2;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 0, 1, 0, 1, 0, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    char *test_str = "get_max_priority/testB";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Constructing a ten element list", 
                                      test_str);
    tm_get_max_priority_helper(tm, max_priority, 
                               "tm_get_max_priority: many tasks", test_str);
}


/***************************************************************/
TestSuite(tm_get_num_jobs_by_priority, .timeout=60);

void tm_get_num_jobs_by_priority_helper(task_manager_t *tm, 
                                        int expected[], 
                                        char *test_desc,
                                        char *test_str)
{
    int actual[tm->max_priority+1];
    tm_get_num_jobs_by_priority(tm, actual);
    char err_msg[ERR_MSG_LEN];

    for (int p = 0; p < tm->max_priority+1; p++) {
        snprintf(err_msg, ERR_MSG_LEN-1,
                 ("Failed %s\n"
                  "  Actual count for priority %d: %d\n"
                  "  Expected count for priority %d: %d\n"
                  "Command to rerun this test: "
                  "bin/test_task_manager --filter %s\n"),
                 test_desc, p, actual[p], p, expected[p], test_str);

        cr_assert_eq(actual[p], expected[p], " \n%s", err_msg);
    }

    tm_free(tm);
}


Test(tm_get_num_jobs_by_priority, testA) 
{
    char *test_desc = "tm_get_num_jobs_by_priority: no tasks";
    char *test_str = "tm_get_num_jobs_by_priority/testA";
    task_manager_t *tm = mk_zero(test_str);
    int expected[BASIC_MAX_PRIORITY+1];
    for (int p = 0; p <= BASIC_MAX_PRIORITY; p++) {
        expected[p] = 0;
    }
    tm_get_num_jobs_by_priority_helper(tm, expected, test_desc, test_str);
}

Test(tm_get_num_jobs_by_priority, testB) 
{
    char *test_desc = "tm_get_num_jobs_by_priority: one task";
    char *test_str = "tm_get_num_jobs_by_priority/testB";
    task_manager_t *tm = mk_one(test_str);
    int expected[BASIC_MAX_PRIORITY+1];
    for (int p = 0; p < BASIC_MAX_PRIORITY+1; p++) {
        expected[p] = 0;
    }
    expected[BASIC_MAX_PRIORITY] = 1;
    tm_get_num_jobs_by_priority_helper(tm, expected, test_desc, test_str);
}


Test(tm_get_num_jobs_by_priority, testC) 
{
    int max_priority = 2;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 0, 1, 0, 1, 0, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    int expected[] = {4, 4, 2};
    char *test_desc = "get_get_num_jobs_by_priority: many tasks";
    char *test_str = "get_get_num_jobs_by_priority/testC";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Constructing a ten element list",
                                      test_str);                                    
    tm_get_num_jobs_by_priority_helper(tm, expected, test_desc, test_str);
}


/***************************************************************/
TestSuite(tm_remove_task, .timeout=60);

void shift_tasks(int start, int num_tasks, 
                 int tids[], int priorities[], int runtimes[])
{
     for (int i = start; i < num_tasks; i++) {
        // shift all values to left
        tids[i] = tids[i+1];
        priorities[i] = priorities[i+1];
        runtimes[i] = runtimes[i+1];
    }   
}

Test(tm_remove_task, testA) 
{
    int max_priority = BASIC_MAX_PRIORITY;
    int num_tasks = 1;
    int tids[num_tasks];
    int priorities[] = {2};
    int runtimes[] = {10};
    char *test_desc = "tm_remove_task: remove only task";
    char *test_str = "tm_remove_task/testA";

    // Make a task manager with one task
    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "One task",
                                      test_str);

    // remove the only task
    tm_remove_task(tm, tids[0]);
    check_int(tm_get_num_tasks(tm), 0, "task list length", 
              test_desc, test_str);
    verify_and_free_empty_tm(tm, max_priority, test_desc, test_str);
}

Test(tm_remove_task, testB) 
{
    int max_priority = BASIC_MAX_PRIORITY;
    int num_tasks = 1;
    int tids[num_tasks];
    int priorities[] = {2};
    int runtimes[] = {10};
    char *test_desc = ("tm_remove_task: remove a non-existent task"
                       " from a one task list");
    char *test_str = "tm_remove_task/testB";

    // Make a task manager with one task
    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Constructing a one element list",
                                      test_str);

    // remove non-existant task
    tm_remove_task(tm, 14003);
    check_int(tm_get_num_tasks(tm), num_tasks, "task list length", 
              test_desc, test_str);    
    verify_tm(tm, max_priority, 1, 
              tids, priorities, runtimes,
              test_desc, test_str);
    tm_free(tm);
}

Test(tm_remove_task, testC) 
{
    char *test_desc = ("tm_remove_task: remove a non-existent task"
                       " from an empty task list");
    char *test_str = "tm_remove_task/testC";
    task_manager_t *tm = mk_zero(test_str);

    // remove non-existant task
    tm_remove_task(tm, 14003);
    check_int(tm_get_num_tasks(tm), 0, "task list length", 
              test_desc, test_str);      
    verify_and_free_empty_tm(tm, BASIC_MAX_PRIORITY, test_desc, test_str);    
}

Test(tm_remove_task, testD) 
{
    int max_priority = 5;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 3, 1, 4, 1, 5, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    char *test_str = "tm_remove_task/testD";
    char *test_desc = "tm_remove_task: remove last element from ten elements list";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten element list", test_str);
    // remove the last task
    int task_to_remove = tids[num_tasks - 1];
    tm_remove_task(tm, task_to_remove);
    check_int(tm_get_num_tasks(tm), num_tasks-1, "task list length", 
              test_desc, test_str);      
    verify_tm(tm, max_priority, num_tasks-1, 
              tids, priorities, runtimes,
              test_desc, test_str);
    tm_free(tm);
}

Test(tm_remove_task, testE) 
{
    int max_priority = 5;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 3, 1, 4, 1, 5, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    char *test_str = "tm_remove_task/testE";
    char *test_desc = "tm_remove_task: remove first task from ten task list";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten task list", test_str);

    // remove the last task
    int index_task_to_remove = 0;
    int task_to_remove = tids[index_task_to_remove];
    shift_tasks(index_task_to_remove, num_tasks,tids, priorities, runtimes);

    tm_remove_task(tm, task_to_remove);
    check_int(tm_get_num_tasks(tm), num_tasks-1, "task list length", 
              test_desc, test_str);      
    verify_tm(tm, max_priority, num_tasks-1, 
              tids, priorities, runtimes,
              test_desc, test_str);
    tm_free(tm);
}

Test(tm_remove_task, testF) 
{
    int max_priority = 5;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 3, 1, 4, 1, 5, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    char *test_str = "tm_remove_task/testF";
    char *test_desc = "tm_remove_task: remove middle task from ten task list";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten task list", test_str);

    // remove the last task
    int index_task_to_remove = 5;
    int task_to_remove = tids[index_task_to_remove];
    shift_tasks(index_task_to_remove, num_tasks,tids, priorities, runtimes);

    tm_remove_task(tm, task_to_remove);
    check_int(tm_get_num_tasks(tm), num_tasks-1, "task list length", 
              test_desc, test_str);      
    verify_tm(tm, max_priority, num_tasks-1, 
              tids, priorities, runtimes,
              test_desc, test_str);
    tm_free(tm);
}

Test(tm_remove_task, testG) 
{
    int max_priority = 5;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 3, 1, 4, 1, 5, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    char *test_str = "tm_remove_task/testG";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten task list", test_str);

    // remove non-existent task
    int task_to_remove = 14003;
    char *test_desc = "tm_remove_task: remove a non-existent TID from 10 task list";    
    tm_remove_task(tm, task_to_remove);
    check_int(tm_get_num_tasks(tm), num_tasks, "task list length", 
              test_desc, test_str);      
    verify_tm(tm, max_priority, num_tasks, 
              tids, priorities, runtimes,
              test_desc, test_str);
    tm_free(tm);
}

/***************************************************************/
TestSuite(tm_run_cycle, .timeout=60);

void tm_run_cycle_helper(task_manager_t *tm, int num_tasks, int max_priority,
                         int tids[], int runtimes[], int priorities[], int slices[],
                         char *test_desc, char *test_str)
{                         
    int actual = tm_run_cycle(tm, slices);

    // be lazy: may allocate more space than needed.
    int expected = 0;
    int new_tids[num_tasks];
    int new_priorities[num_tasks];
    int new_runtimes[num_tasks];
    int next_open_slot = 0;
    for (int i = 0; i < num_tasks; i++) {
        int sp = slices[priorities[i]];
        int at = (sp <= runtimes[i] ? sp : runtimes[i]);
        expected += at;
        if ((runtimes[i] - at) > 0) {
            new_tids[next_open_slot] = tids[i];
            new_priorities[next_open_slot] = priorities[i];
            new_runtimes[next_open_slot] = runtimes[i] - at;
            next_open_slot++;
        }
    }

    check_int(actual, expected, "total running time", test_desc, test_str);

    if (next_open_slot == 0) {
        verify_and_free_empty_tm(tm, max_priority, test_desc, test_str);
    } else {
        verify_tm(tm, max_priority, next_open_slot, 
                  new_tids, new_priorities, new_runtimes,
                  test_desc, test_str);   
    } 
}

Test(tm_run_cycle, testA) 
{
    int max_priority = BASIC_MAX_PRIORITY;
    int num_tasks = 1;
    int tids[num_tasks];
    int priorities[] = {2};
    int runtimes[] = {10};
    char *test_str = "tm_run_cycle/testA";

    // Make a task manager with one task
    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "One task",
                                      test_str);

    int slices[] = {10, 10, 5};
    char *test_desc = "tm_run_cycle: one task that does not finish";    
    tm_run_cycle_helper(tm, num_tasks, max_priority, tids, runtimes, priorities,
                        slices, test_desc, test_str);
}

Test(tm_run_cycle, testB) 
{
    int max_priority = BASIC_MAX_PRIORITY;
    int num_tasks = 1;
    int tids[num_tasks];
    int priorities[] = {2};
    int runtimes[] = {10};
    char *test_str = "tm_run_cycle/testB";

    // Make a task manager with one task
    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Constructing a one element list", test_str);

    // one task that finishes
    int slices[] = {10, 10, 10};
    char *test_desc = "Running one cycle w/ one task that does not finish";    
    tm_run_cycle_helper(tm, num_tasks, max_priority, tids, runtimes, priorities,
                        slices, test_desc, test_str);
}

Test(tm_run_cycle, testC) 
{
    int max_priority = BASIC_MAX_PRIORITY;
    int num_tasks = 1;
    int tids[num_tasks];
    int priorities[] = {2};
    int runtimes[] = {10};
    char *test_str = "tm_run_cycle/testC";

    // Make a task manager with one task
    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Constructing a one element list",
                                      test_str);

    // More time than needed
    int slices[] = {10, 10, 20};
    char *test_desc = ("Running one cycle w/ one task that finishes"
                       " in under the alloted time");
    tm_run_cycle_helper(tm, num_tasks, max_priority, tids, 
                        runtimes, priorities,
                        slices, test_desc, test_str);
}

Test(tm_run_cycle, testD) 
{
    char *test_str = "tm_remove_task/testD";
    int slices[] = {10, 10, 20};
    char *test_desc = "Run cycle: one cycle with zero tasks";  
    task_manager_t *tm = mk_zero(test_str);
    tm_run_cycle_helper(tm, 0, BASIC_MAX_PRIORITY, NULL, 
                        NULL, NULL,
                        slices, test_desc, test_str);                
}

Test(tm_run_cycle, testE) 
{
    int max_priority = 5;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 3, 1, 4, 1, 5, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    // Will remove all tasks
    int slices[] = {10, 10, 20, 10, 10, 5};
    char *test_desc = "Run cycle: all ten tasks finish";
    char *test_str = "tm_run_cycle/testE";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten task list", test_str);
    tm_run_cycle_helper(tm, num_tasks, max_priority, tids, 
                        runtimes, priorities,
                        slices, test_desc, test_str);            
}

Test(tm_run_cycle, testF) 
{
    int max_priority = 5;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 3, 1, 4, 1, 5, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    // Will complete all tasks
    int slices[] = {1, 1, 1, 1, 1, 1};
    char *test_desc = "Run cycle: five of ten tasks finish"; 
    char *test_str = "tm_run_cycle/testF";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten task list", test_str);
    tm_run_cycle_helper(tm, num_tasks, max_priority, tids, 
                        runtimes, priorities,
                        slices, test_desc, test_str);                  
}

Test(tm_run_cycle, testG) 
{
    int max_priority = 9;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    // Will complete the last task only
    int slices[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 5};
    char *test_desc = "Run cycle: five of ten tasks finish";
    char *test_str = "tm_run_cycle/testG";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten task list", test_str);
    tm_run_cycle_helper(tm, num_tasks, max_priority, tids, 
                        runtimes, priorities,
                        slices, test_desc, test_str);                
}

Test(tm_run_cycle, testH) 
{
    int max_priority = 9;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    // Will complete the first task only
    int slices[] = {20, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char *test_desc = "Run cycle: five of ten tasks finish";
    char *test_str = "tm_run_cycle/testH";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten task list", test_str);
    tm_run_cycle_helper(tm, num_tasks, max_priority, tids, 
                        runtimes, priorities,
                        slices, test_desc, test_str);            
}

Test(tm_run_cycle, testI) 
{
    int max_priority = 9;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    // Will complete a middle task only
    int slices[] = {0, 0, 0, 0, 10, 0, 0, 0, 0, 0};
    char *test_desc = "Run cycle: five of ten tasks finish";    
    char *test_str = "tm_run_cycle/testI";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten task list", test_str);
    tm_run_cycle_helper(tm, num_tasks, max_priority, tids, 
                        runtimes, priorities,
                        slices, test_desc, test_str);              
}

Test(tm_run_cycle, testJ)
{
    int max_priority = 5;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 3, 1, 4, 1, 5, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    int slices[] = {5, 5, 10, 10, 10, 10};
    char *test_desc = "Run cycle: five of ten tasks finish";    
    char *test_str = "tm_run_cycle/testJ";

    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten task list", test_str);
    tm_run_cycle_helper(tm, num_tasks, max_priority, tids, 
                        runtimes, priorities,
                        slices, test_desc, test_str);                 
}

/***************************************************************/
TestSuite(run_tasks, .timeout=60);

void run_tasks_helper(task_manager_t *tm, int slices[], int max_priority,
                      int expected_cycle_count, int expected_total_time,
                      char *test_desc, char *test_str)
{
    int actual_total_time;
    int actual_cycle_count = run_tasks(tm, slices, &actual_total_time);

    check_int(actual_total_time, expected_total_time, "total time",
                test_desc, test_str);
    check_int(actual_cycle_count, expected_cycle_count, "cycle count",
                test_desc, test_str);                
    verify_and_free_empty_tm(tm, max_priority, test_desc, test_str);
}

Test(run_tasks, testA) 
{
    int max_priority = BASIC_MAX_PRIORITY;
    int num_tasks = 1;
    int tids[num_tasks];
    int priorities[] = {max_priority};
    int runtimes[] = {10};
    char *test_str = "run_tasks/testA";

    // Make a task manager with one task
    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "One task", test_str);

    int slices[] = {10, 10, 10};
    char *test_desc = "tm_run_cycle: Running one task that takes one cycle";
    int expected = add_int_array(runtimes, num_tasks);
    run_tasks_helper(tm, slices, max_priority,
                     1, expected,
                     test_desc, test_str);
}

Test(run_tasks, testB) 
{
    int max_priority = BASIC_MAX_PRIORITY;
    int num_tasks = 1;
    int tids[num_tasks];
    int priorities[] = {max_priority};
    int runtimes[] = {10};
    char *test_str = "run_tasks/testB";

    // Make a task manager with one task
    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "One task", test_str);

    int slices[] = {10, 10, 2};
    char *test_desc = "tm_run_cycle: Running one task that takes five cycles";
    int expected = add_int_array(runtimes, num_tasks);
    run_tasks_helper(tm, slices, max_priority,
                     5, expected,
                     test_desc, test_str);
}

Test(run_tasks, testC) 
{
    int max_priority = BASIC_MAX_PRIORITY;
    int num_tasks = 1;
    int tids[num_tasks];
    int priorities[] = {max_priority};
    int runtimes[] = {10};
    char *test_str = "run_tasks/testC";

    // Make a task manager with one task
    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "One task", test_str);

    int slices[] = {10, 10, 4};
    char *test_desc = "tm_run_cycle: Running one task that takes three cycles";
    int expected = add_int_array(runtimes, num_tasks);
    run_tasks_helper(tm, slices, max_priority,
                     3, expected,
                     test_desc, test_str);
}

Test(run_tasks, testD) 
{
    char *test_str = "run_tasks/testD";
    // Make a task manager with one task
    task_manager_t *tm = mk_zero(test_str);

    int slices[] = {10};
    char *test_desc = "tm_run_cycle: zero tasks";
    run_tasks_helper(tm, slices, BASIC_MAX_PRIORITY,
                     0, 0,
                     test_desc, test_str);
}

Test(run_tasks, testE) 
{
    int max_priority = 5;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 3, 1, 4, 1, 5, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    char *test_str = "run_tasks/testE";

    // Make a task manager with one task
    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten tasks", test_str);

    int slices[] = {10, 10, 20, 10, 10, 5};
    char *test_desc = "tm_run_cycle: Running ten tasks; takes one cycle";
    int expected = add_int_array(runtimes, num_tasks);
    run_tasks_helper(tm, slices, max_priority,
                     1, expected,
                     test_desc, test_str);
}

Test(run_tasks, testF) 
{
    int max_priority = 5;
    int num_tasks = 10;
    int tids[num_tasks];
    int priorities[] = {2, 0, 1, 3, 1, 4, 1, 5, 1, 2};
    int runtimes[] = {20, 10, 10, 10, 10, 10, 10, 5, 5, 5};
    char *test_str = "run_tasks/testF";

    // Make a task manager with one task
    task_manager_t *tm = mk_sample_tm(max_priority, num_tasks, 
                                      priorities, runtimes, tids,
                                      "Ten tasks", test_str);

    int slices[] = {5, 10, 5, 10, 10, 5};
    char *test_desc = "tm_run_cycle: Running ten tasks; takes four cycles";
    int expected = add_int_array(runtimes, num_tasks);
    run_tasks_helper(tm, slices, max_priority,
                     4, expected,
                     test_desc, test_str);
}
