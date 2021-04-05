/* CMSC 15200, Winter 2021
 *  PA #3 Task Manager: Source file for a task scheduler
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "task_manager.h"
#include "scheduler.h"

/* run_tasks: run task manager cycles until all the tasks have finished
 *
 * tm: a task manager
 * time_slices: array with time slices for each
 *   priority.
 * total_time_ptr: a pointer to the total time runned until all the tasks
 *   have finished
 * 
 * Returns: the number of cycles run
 */
int run_tasks(task_manager_t *tm, int time_slices[], int *total_time_ptr)
{
  int cycles = 0;
  int num_tasks = tm_get_num_tasks(tm);
  *total_time_ptr = 0;

  while (num_tasks > 0) {
    *total_time_ptr += tm_run_cycle(tm, time_slices);
    cycles ++;
    num_tasks = tm_get_num_tasks(tm);
  }
  return cycles;
}
