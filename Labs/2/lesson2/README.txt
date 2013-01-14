Laboratory work #2

Goal

	--make the output to screen easy:
		
		-implement putc (print a character at the current cursor position and increase the position of the cursor)
		
		-implement puts (print a caracter at the current cursor position, and advance the position of the cursor with the length of the string)

		-implement clrscr (clear the screen)

	-- create a command prompt which can read and parse commands, and will respond to all commands with "you typed: <command>"
	  implement gets (get a string from keyboard)
		
		-when a command is typed, the output should be written below the command and the prompt should be moved below the output
		
		-(optional) when the prompt reaches the bottom, the whole text should scroll up, and the prompt should stay at the bottom of the screen. (+10 EXP)

Short description of functions

gets() - a series of getchar's that write the character to a string, until Enter is pressed
putc() - outputs one char to vidmem, using the current index (global variable i) it writes the character that will be output to 
		vidmem[i] and the attributes (color/background) to the next position (i++)
puts() - a series of putc(), having as input the address of the first element of the string to be output.
scrollDown() - obviously executes scrolling. How? - copying the the last m lines (where m>0) to lines 0 through n-m, this way leaving 
				n-m lines free
NewLine() - increments the index (i) so that the prompt passes to the new line 
strcmp() - an implementation of the original C function for comparing 2 strings. Returns 1 or 0 if the strings are equal or not (respectively)
CommandPrompt() - reads one input string and either executes the respective command or prints "You typed:\n" + [input String]


How it was done

	For implementing all the functions I used the getchar() function that was available. Gets, represents a sequence of getchars saving the data to a string. To determine if the user finished the input of text, before adding the char to the string, it was compared to '\n' (Enter pressed).

	For putc(), was used the  magic vidmem starting address. Puts – a bunch of putc() stitched together. The only difference was, that puts, as it is in C, passes on to the next line, to implement this I have just considered the number of characters in a row and added this number to the index. 
	Clrscr(), simply returns to the first element of vidmem, and then fills the entire screen with spaces. Then resets the index to 0.

	All the functions related to the command prompt simulation, are included with the video.c file.