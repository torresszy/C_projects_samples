#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct task task_t;

enum task_status {TASK_DONE, TASK_RESCHEDULE, TASK_KEEP};


/* mk_task: create an new task
 *
 * tid - task ID for the task
 * priorty - priority for the task
 * run_time - running time for the task
 * 
 * Returns: a pointer to a task
 */
task_t *mk_task(int tid, int priority, int run_time);


/* free_task: frees the nodes a circular TASK
 *
 * lst - a circular TASK
 */
void free_task(task_t *task);


/* task_cmp -- determine which of two tasks is more urgent.
 *
 * task1 -- a pointer to a task
 * task2 -- a pointer to a task
 *
 * Returns:
 *   < 0 -- if task1 is more urgent than task2 '
 *   > 0 -- if task2 is more urgent than task1
 *  == 0 -- if task1 and task2 are equally as urgent
 */
int cmp_task(task_t *task1, task_t *task2);

/* print_task -- optional function that prints the information in a task
 *
 * task -- a pointer to a task
 */
void print_task(task_t *task);


/* execute_task - do one time slice of work for a task
 *
 * task: a pointer to a task
 * time_slice: the maximum amount of time to execute the task in this cycle
 * execution_time_pointer: an OUT parameter for returning the amount of time actually executed.
 *
 * Returns: 
 *   TASK_DONE if the task is finished
 *   TASK_KEEP if the task has less than KEEP_THRESHOLD time left
 *   TASK_RESCHEDULE otherwise
 */
enum task_status execute_task(task_t *task, int time_slice, int *execution_time_ptr);
