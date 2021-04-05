/* CMSC 15200, Winter 2021
 *  PA #3 Task Manager: Header file for task manager
 */

#include <stdbool.h>

typedef struct task_manager task_manager_t;

/* tm_create: create an empty task manager
 *
 * max_priority: task priorities will run from 0 to max_priority (inclusive).
 *
 * Returns: task manager
 */
task_manager_t *tm_create(int max_priority);


/* tm_free: free all the space associated with a task manager
 *
 * tm: a task manager
 */
void tm_free(task_manager_t *tm);


/* tm_print: (optional) print the contents of the task manager list 
 *
 * tm: a task manager
 */
void tm_print(task_manager_t *tm);


/* tm_is_empty: is the task manager empty?
 *
 * tm: a task manager
 *
 * Returns: true is there are zero tasks on the task list,
 *  false otherwise.
 */
bool tm_is_empty(task_manager_t *tm);


/* tm_add_task: add a new task with the specified priority and
 *   running time to the end of the task list.
 *
 * tm: a task manager
 * priority: the priority for the task (must be between 0 and
 *  the maximum priority specified in the task manager (inclusive)
 * run_time: the running time of the task
 *
 * Returns: a unique identifier for the task as an integer
 */
int tm_add_task(task_manager_t *tm, int priority, int run_time);


/* tm_remove_task: remove the specified task from the task manager if
 *   it exists
 *
 * tm: a task manager
 * tid: a task identifier
 *
 * Returns: true if task with task identifier tid has been removed from the list,
 *  false if no such task existed
 */
bool tm_remove_task(task_manager_t *tm, int tid);


/* tm_get_num_tasks: return the number of tasks on the list
 *
 * tm: a task manager
 *
 * Returns: the number of tasks on the list as an integer
 */
int tm_get_num_tasks(task_manager_t *tm);


/* tm_get_max_priority: get the maximum priority associated with a task manager
 *
 * tm: a task manager
 *
 * Returns: returns the maximum priority associated with a task manager as an integer
 */
int tm_get_max_priority(task_manager_t *tm);


/* tmp_get_num_jobs_by_priority: count the number of tasks for each priority level
 *
 * tm: a task manager 
 * count_by_priority: the array in which to store the counts.  Must be
 *   big enough to hold counts for prioritys from 0 to the tm's max
 *   priority (inclusive)
 */
void tm_get_num_jobs_by_priority(task_manager_t *tm, int count_by_priority[]);


/* tm_run_cycle: Runs each task for the length of time specified for
 *   its priority. Removes tasks that are finished from the task list.
 *
 * tm: a task manager
 * time_slice_per_priority: array with time slices for each
 *   priority. The pth entry is the maximum amount of time to run
 *   a given task of priority p.  Assume there are enough entries
 *   for 0 to the tm's max priority (inclusive).
 * 
 * Returns: the total time executed for the tasks
 */ 
int tm_run_cycle(task_manager_t *tm, int time_slice_per_priority[]); 


