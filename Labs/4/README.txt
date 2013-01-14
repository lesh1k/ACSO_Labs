Laboratory work #4

Goal

	-- Integrate setjmp and longjmp in your project.

How it was done

	We had 3 sources: a special data-structure definition, used for storing registers' data, the functions for saving and reading the stored data.
	longjmp.c contains one additional function, so we simply paste the file to the lib folder. The datastructure should be available in the program and first of all accessible by the function thus we include the header file containing the data structure into longjmp.c and include the latter into our kmain.c
	The last file, setjmp.asm, contains assembly code, we copy it entirely and paste in the loader.asm file where we have the other assembly code.

What do setjmp.asm and longjmp.c do?

	Setjmp() and longjmp() are subroutines that let us perform complex flow-of-control in C/Unix. Saves the current state of the registers into the buffer (jmp_buf).
	Longjmp() resets the registers to the values saved in buffer. 