#include "lib/video.c"
#include "lib/longjmp.c"
#include "lib/task.h"


//Global variables

// Fixed tasks array (4 tasks)
task_t _sched_tasks[3];  
//number of added tasks
int task_added = 0;
// current task
int _sched_num_tasks = 0;


void sched_add_task (void* func_ptr) {
  task_t *task = & _sched_tasks[++_sched_num_tasks];
  unsigned* initial_stack_ptr;

  //The task comes with the current context as default
  sched_save_state(task);
  initial_stack_ptr = (unsigned) task->stack + TASK_STACK_SIZE;

  /// set stack pointer of the task context to initial_stack_ptr
  task->state[0].esp = initial_stack_ptr;
  // set instruction pointer of the task context to func_ptr
  task->state[0].eip=func_ptr;
  // set status of the task as runnable
  task->status=1;

void yield(void){

// switch context from current task to next
	sched_switch_context(current_task(),next_task());
}

void sched_run(void){


}




int main( void )
{  
 char* vidmem = (char *) 0xb8000;

void task0 (void) {
  while (1) {
    yield();
    vidmem[0] = vidmem[0] == 'B' ? 'A' : 'B';
    wait();
  }
}

void task1 (void) {
  while (1) {
    yield();
    vidmem[2] = vidmem[2] == 'B' ? 'A' : 'B';
    wait();
  }
}

int main( void )
{
  vidmem[1] = 0x7;
  vidmem[3] = 0x7;
  sched_add_task(task0);
  sched_add_task(task1);
  sched_run();
}
}