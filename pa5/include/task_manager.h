/* CMSC 15200, Winter 2021
 *  PA #5 Task Manager: header file for the PA #5 task manager
 */

typedef struct task_manager task_manager_t;

/* tm_create: create an empty task manager
 *
 * Returns: a pointer to a task manager
 */
task_manager_t *tm_create();

/* tm_free: free all the space associated with a task manager and with any tasks that
 *   are still in the heap.
 *
 * tm: a pointer to a task manager
 *
 */
void tm_free(task_manager_t *tm);

/* tm_print: (optional) print the contents of the heap
 *
 * tm: a pointer to a task manager
 *
 */
void tm_print(task_manager_t *tm);

/* tm_is_empty: is the task manager empty?
 *
 * tm: a pointer to a task manager
 * 
 * Returns: true is there are no tasks in the heap
 *   false otherwise.
 */
bool tm_is_empty(task_manager_t *tm);

/* tm_add_task: add a new task to the task manager
 *
 * tm: a pointer to a task manager
 * task: a pointer to a task
 *
 */
void tm_add_task(task_manager_t *tm, task_t *task);

/* tm_remove_most_urgent: remove the most urgent task from the task
 *   manager.
 *
 * tm: a pointer to a task manager
 *
 * Returns: a pointer to the most urgent task or NULL, if the task
 *   manager has no tasks.
 */
task_t *tm_remove_most_urgent_task(task_manager_t *tm);
