## Goal

*   set up build environment
*   launch hello world OS successfully with the message displayed on screen. 

### Setup
**Linux**

If you're on Linux, thanks, because you made my life 2 times easier. The development process is rather simple using it.

**Prerequisites**: gcc v.4+, build-essential (*make* and other simple stuff)

If you're on ubuntu, just do a `sudo apt-get install build-essential`

To get you project running:

*   [download lab1 materials](http://www.mediafire.com/?ldutfa0lr2g4kq2)
*   open a shell and cd where you extracted the archive
*   `make clean`
*   `make`

**Windows**

* Import OSDev.ova (it's a virtual machne where we will compile the project)
* Install winssh-fs
* Launch the imported OS
* create a drive with winssh-fs to address 192.168.56.101 with login: ubu, password: qwe
* go to the launched machine:
	* `cd lesson1`
	* `make clean`
	* `make`

## Running
A file named helloworld.img will appear in the lesson1 folder (or on the ssh drive you mounted), use it as a floppy image for a Virtual Machine, launch it, and the text should appear on the screen.

# Stuff I will be asking
(*categorized by difficulty*)

*   I'm too young to die 
    *   what is a boot process?
    *   how to make a drive bootable?
*   Hurt me plenty 
    *   why we didn't use printf in hello world example?
* Nightmare
	* What's with the contents of bloader.h? Why it is there?