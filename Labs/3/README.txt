Laboratory work #3

Goal

	-- Provide the ability to load a task

How it was done

	Since the ability to execute tasks was implemented in the previous laboratory work, I had to
	replace the old Makefile with the new one, we were provided with. Then, create a new folder named "cmd", where I created 2 functions "cmd_hello.c" and "cmd_happiness.c". To make use of these, two if-statements were used to compare whether the 
	input corresponds to any of the existing functions, if so, the respective function was executed.

Available commands:

	hello - prints out "Hello!"
	happiness - prints several different smiles
	clrscr (not in the cmd folder, inherited since lab #2) - clears the screen.