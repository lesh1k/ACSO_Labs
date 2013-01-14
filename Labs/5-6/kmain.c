#include "lib/io.c"
#include "lib/kbd.c"
#include "lib/video.c"
#include "lib/longjmp.c"


#define TASK_STACK_SIZE 512

typedef enum 
{
  TS_RUNNABLE = 1, TS_BLOCKED = 2, TS_ZOMBIE = 3
} task_status_t;


typedef struct 
{
    jmp_buf state;
    task_status_t status;
    unsigned char stack[TASK_STACK_SIZE];
} task_t;


task_t tasks[2];
int task_nr = 0;
current_task_nr = 0;


void sched_add_task(void * func_ptr) 
{

    task_t * task = & tasks[task_nr];
    task_nr++;

    int i;
    i = setjmp(task->state);
    if (!i) 
    {
        unsigned * initial_stack_ptr;
        initial_stack_ptr = (unsigned) task->stack + TASK_STACK_SIZE;

        task->state[0].esp = initial_stack_ptr;
        task->state[0].eip = func_ptr;
        task->state[0].eflags = 0x200; 
     }
}


void sched_run() 
{
    current_task_nr = 0;
    longjmp(tasks[0].state, 1);
}


void yield() 
{
    if (!setjmp(tasks[current_task_nr].state)) 
    {
        if (current_task_nr == 0) 
        {
            current_task_nr = 1;
        }
         else 
         {
            current_task_nr = 0;
        }
        longjmp(tasks[current_task_nr].state, 1);
    }
}

* vidmem = (char *) 0xb8000;

void wait() 
{
  int a, b;
  for ( a = 1 ; a <= 3000 ; a++ ) 
  for ( b = 1 ; b <= 3000 ; b++ );
}

void task0 (void) 
{
  while (1) 
  {
    yield();
    vidmem[0] = vidmem[0] == 'B' ? 'A' : 'B';
    wait();
  }
}

void task1 (void) 
{
  while (1) 
  {
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