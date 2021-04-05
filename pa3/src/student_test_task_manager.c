/* CMSC 15200, Winter 2021
 *  PA #3 Task Manager: Source file for student test code
 */


#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "task_manager.h"
#include "scheduler.h"

task_manager_t *mk_sample(int max_priority, int num_tasks)
{
    task_manager_t *tm = tm_create(max_priority);
    int tid[num_tasks];

    // start with one maximum priority task 
    tm_add_task(tm, max_priority, 20);

    // add in num_tasks-1 more tasks. Assign priorities                                               
    // (0..max_priority-1) round robin.  Use a fixed                                                  
    // running time for simplicity.                                                                   
    int priority = 0;
    for (int i = 0; i < num_tasks - 1; i++) {
        // use a fixed running time for simplicity.
        tid[i] = tm_add_task(tm, priority, 10);
        priority = (priority + 1) % max_priority;
    }

    return tm;
}

int main()
{
    int max_priority = 2;
    int num_tasks = 10;
    
    // construct and print a sample task manager
    task_manager_t *tm = mk_sample(max_priority, num_tasks);
    tm_print(tm);

    // Run the functions to get basic information from the task manager
    printf("Is empty? %s\n", tm_is_empty(tm) ? "true" : "false");
    printf("Maximum priority: %d\n", tm_get_max_priority(tm));
    printf("Number of tasks: %d\n", tm_get_num_tasks(tm));

    // Run the function that counts by priority
    int priority_counts[max_priority + 1];
    tm_get_num_jobs_by_priority(tm, priority_counts);
    printf("Count by priority:");
    for (int p = 0; p <= max_priority; p++)
    {
        printf("%d ", priority_counts[p]);
    }
    printf("\n\n");

    // Add and remove a few tasks
    // print the rest.
    // assumes task IDs start at zero and increase by 1 each time.
    tm_remove_task(tm, 0);
    tm_remove_task(tm, 9);
    tm_remove_task(tm, 5);
    tm_add_task(tm, 2, 5);
    tm_add_task(tm, 0, 20);
    printf("After adds and removes\n");
    tm_print(tm);

    // Run one cycle and print the resulting TM
    int slices[] = {10, 5, 2};
    tm_run_cycle(tm, slices);
    printf("After run cycle\n");
    tm_print(tm);

    // Done with this task manager
    tm_free(tm);

    // Start w/ original task manager and run the tasks to completion.
    tm = mk_sample(max_priority, num_tasks);
    int total_time;
    int num_cycles = run_tasks(tm, slices, &total_time);
    printf("Running the tasks took %d cycles and %d total_time\n",
           num_cycles, total_time);

    // Check that the task manager is empty upon completion.
    printf("Empty after full run? %s\n", tm_is_empty(tm) ? "true" : "false");

    // free up the task manager
    tm_free(tm);
}
