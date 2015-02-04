# Call Stacks and System Calls

## Call Stacks
stacks.c defines some functions to demonstrate some characteristics of the call stack. To note:
- The call stack starts at some number and as you call each function, gets smaller (ie: stacks grow downwards on x86 architectures)
- The more / larger arguments that are on the stack, the more the call stack grows per iteration.

A decent guide to the x86 calling convention can be [found here](http://duartes.org/gustavo/blog/post/journey-to-the-stack/). A lot of the rules for mapping between C and its compiled assembly are available for compilers to alter as they see fit (often for performance reasons), except when making system calls. More on that below.


## System Calls
Useful information about the syscall() function exists in the [syscall man page](http://man7.org/linux/man-pages/man2/syscall.2.html). However, for a high level overview the [Wikipedia Article](http://en.wikipedia.org/wiki/System_call) is pretty decent.

Things to keep in mind:
- Programs run in a sandbox and (generally) don't have direct access to the hardware
- The OS kernel defines the interface with hardware and programs have to use the interface provided to do things like reading / writing to files
- The kernel and your program do not share logical memory space. That is to say, your program can't directly read or write to memory owned by the kernel
    
## Pass by Value / Pass by Reference
This should be the last little bit of information about memory that you'd need to know before we can talk about data structures. It demonstrates some basics about how arguments can be passed in C.
