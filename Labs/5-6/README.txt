Laboratory work #5

Goal

	-- implement simple multi-tasking
	-- the OS multitasking should have the following functions available:
			void sched_add_task(void* func_ptr) – add a task to scheduler by giving a function pointer
			void yield(void) – give control to scheduler in a task
			void sched_run(void) – start the scheduler

How it can be done.

	Provided with the materials (functions skeletons, data strucutres definitions) must be first of all placed in the right 
	files/folders. Although for simplicity, these can be just pasted into kmain.c
	The main idea is implementing the ability of switching between functions, for this,
	setjmp (for storing current task state) and longjmp (for fetching the state of the task) will be used.
	For storing tasks, simply use a fixed size array.
	Each task includes yield(), that allows cooperative multi-tasking (passing to the next task from the inside of the current task and similarly back). In order that the switching between tasks does not occur too fast, a wait function should be
	added. It can be implemented simply just as a loop with very big number of iterations.

How it works.

	In our case, we have 2 functions that write a character to vidmem[], either A or B, depending on the one, previously
	written. Each task is given an index/order number, so that it could be easily differentiated by the scheduler.
	Sooo, first of all we must have two functions, add these to the scheduler (sched_run(void)) which in its turn uses the 
	yield() function (based on longjmp) to switch the context. Enjoy multitasking :))
