/* CMSC 15200, Winter 2021
 *  PA #3 Task Manager: Source file for task manager
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "task_manager.h"

/********* Do NOT modify the type definitions *********/

/* Doubly-linked list (DLL) of tasks */
typedef struct dll_node dll_t;

 
/* Definition of the nodes for doubly-lined list of tasks.
 * DLL must have a dummy head node and be circular: the next field in the last 
 * node in the list should point to the dummy node and the prev field of 
 * the dummy node points to the last node in the list.  An empty list will have
 * exactly one node (the dummy node) with pointers back to itself for 
 * both the next and prev fields. 
 */
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

/********* End type definitions *********/


/* create_node: creates a task
 *
 * priority: priority of the task created.
 * tid: the identifier of the task created.
 * run-time: the amount of run time of the task created
 *
 * Returns: a dll_t pointer to the new task
 */
dll_t* create_node(int tid, int priority, int run_time)
{
    dll_t* node = (dll_t*)malloc(sizeof(dll_t));
    
    node->tid = tid;
    node->priority = priority;
    node->run_time = run_time;

    return node;
}


/* tm_create: create an empty task manager
 *
 * max_priority: task priorities will run from 0 to max_priority (inclusive).
 *
 * Returns: task manager
 */
task_manager_t *tm_create(int max_priority)
{
    task_manager_t* rv = (task_manager_t*)malloc(sizeof(task_manager_t));
    rv->max_priority = max_priority;
    rv->next_tid = 0;

    rv->task_list = create_node(-1, -1, -1);
    rv->task_list->next = rv->task_list;
    rv->task_list->prev = rv->task_list;

    return rv;
}


/* tm_free: free all the space associated with a task manager
 *
 * tm: a task manager
 */
void tm_free(task_manager_t *tm)
{
    dll_t* curr = tm->task_list->next;
    dll_t* target;

    while(curr != tm->task_list) {
        target = curr;
        free(target);
        curr = curr->next;
    }
    free(tm->task_list);
    free(tm);
}


/* tm_print: (optional) print the contents of the task manager list 
 *
 * tm: a task manager
 */
void tm_print(task_manager_t *tm)
{
    dll_t* curr = tm->task_list->next;

    while (curr != tm->task_list) {
        printf("Task %d: %d seconds at priority %d\n", curr->tid, curr->run_time, curr->priority);
        curr = curr->next;
    }
}


/* tm_is_empty: is the task manager empty?
 *
 * tm: a task manager
 *
 * Returns: true is there are zero tasks on the task list,
 *  false otherwise.
 */
bool tm_is_empty(task_manager_t *tm)
{
    return (tm->task_list->next == tm->task_list);
}


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
int tm_add_task(task_manager_t *tm, int priority, int run_time)
{
    dll_t* new_task = create_node(tm->next_tid, priority, run_time);
    new_task->next = tm->task_list;
    tm->task_list->prev = new_task;

    dll_t* curr = tm->task_list->next;
    while (curr->next != tm->task_list) {
        curr = curr->next;
    }

    curr->next = new_task;
    new_task->prev = curr;
    tm->next_tid ++;

    return new_task->tid;

}


/* remove_node: remove a task from the task manager
 *
 * target: the pointer to the node needed to be removed
 *
 * Returns: none, removed the node.
 */
void remove_node(dll_t* target) 
{
    target->prev->next = target->next;
    target->next->prev = target->prev;
    free(target);
}


/* tm_remove_task: remove the specified task from the task manager if
 *   it exists
 *
 * tm: a task manager
 * tid: a task identifier
 *
 * Returns: true if task with task identifier tid has been removed from the list,
 *  false if no such task existed
 */
bool tm_remove_task(task_manager_t *tm, int tid)
{
    dll_t* curr = tm->task_list->next;

    while (curr != tm->task_list) {
        if (curr->tid == tid) {
            remove_node(curr);
            return true;
        }
        curr = curr->next;
    }
    return false;
}


/* tm_get_num_tasks: return the number of tasks on the list
 *
 * tm: a task manager
 *
 * Returns: the number of tasks on the list as an integer
 */
int tm_get_num_tasks(task_manager_t *tm)
{
    int rv = 0;
    dll_t* curr = tm->task_list->next;

    while (curr != tm->task_list) {
        rv++;
        curr = curr->next;
    }
    return rv;
}


/* tm_get_max_priority: get the maximum priority associated with a task manager
 *
 * tm: a task manager
 *
 * Returns: returns the maximum priority associated with a task manager as an integer
 */
int tm_get_max_priority(task_manager_t *tm)
{
    return tm->max_priority;
}


/* tmp_get_num_jobs_by_priority: count the number of tasks for each priority level
 *
 * tm: a task manager 
 * count_by_priority: the array in which to store the counts.  Must be
 *   big enough to hold counts for prioritys from 0 to the tm's max
 *   priority (inclusive)
 */
void tm_get_num_jobs_by_priority(task_manager_t *tm, int count_by_priority[])
{   
    int priority = tm_get_max_priority(tm);
    for (int i = 0; i <= priority; i++) {
        count_by_priority[i] = 0;
    }

    dll_t* curr = tm->task_list->next;
    while (curr != tm->task_list) {
        count_by_priority[curr->priority] ++;
        curr = curr->next;
    }
}


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
int tm_run_cycle(task_manager_t *tm, int time_slice_per_priority[])
{
    int total_time = 0;
    dll_t* curr = tm->task_list->next;
    int time_len;

    while (curr!= tm->task_list) {
        time_len = time_slice_per_priority[curr->priority];
        if (curr->run_time <= time_len) {
            total_time += curr->run_time;
            tm_remove_task(tm, curr->tid);
        } else {
            curr->run_time -= time_len;
            total_time += time_len;
        }
        curr = curr->next;
    }
    return total_time;
}
