# Code samples from CSE 3320
The following programs are provided to demonstrate concepts covered in CSE 3320.

## Process related programs
- [fork.c][01] 		Demonstrates a simple forking of a child process
- [waitpid.c][02]	Demonstrates how to wait on a specific child process and also determine why the child process died
- [exec.c][03]		Fork a child and then call exec to turn the child into an ls process

## Inter-process communication related programs
- [pipe.c][05]	Open a pipe between two processes and write a string from one to the other
- [pipe_redirect.c][06]	Open a pipe between two processes and redirect stdin and stdout 

## Signal handling programs
- [sigint.c][07]	Registering a signal handler, with signal(), to catch a ctrl-c (SIGINT)
- [sigint_sigaction_block.c][08]	Registering a signal handler, with sigaction(), to catch a ctrl-c (SIGINT). Also demonstrates masking (blocking) signals

## Unrelated related programs
- [endien.c][04] 	Determine if your machine is big endien or little endien 

[01]:https://github.com/CSE3320/Code-Samples/blob/master/fork.c
[02]:https://github.com/CSE3320/Code-Samples/blob/master/waitpid.c
[03]:https://github.com/CSE3320/Code-Samples/blob/master/exec.c 
[04]:https://github.com/CSE3320/Code-Samples/blob/master/endien.c 
[05]:https://github.com/CSE3320/Code-Samples/blob/master/pipe.c 
[06]:https://github.com/CSE3320/Code-Samples/blob/master/pipe_redirect.c 
[07]:https://github.com/CSE3320/Code-Samples/blob/master/sigint.c 
[08]:https://github.com/CSE3320/Code-Samples/blob/master/sigint_sigaction_block.c 
