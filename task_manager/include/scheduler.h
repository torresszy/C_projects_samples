/* CMSC 15200, Winter 2021
 *  PA #3 Task Manager: Header file for simple task scheduler
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "task_manager.h"

/* run_tasks: run all the tasks to completion, one cycle at a time.
 *
 * tm: a task manager
 * time_slice_per_priority: array with time slices for each
 *   priority. The pth entry is the maximum amount of time to run
 *   a given task of priority p.  Assume there are enough entries
 *   for 0 to the tm's max priority (inclusive).
 * total_time_ptr: OUT parameter for the total execution time for the tasks
 *
 *  Returns: the number of cycles needed to complete all the tasks as an integer.
 */
int run_tasks(task_manager_t *tm, 
              int time_slice_per_priority[], 
              int *total_time_ptr);



