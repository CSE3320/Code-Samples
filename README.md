# Code samples from CSE 3320
The following programs are provided to demonstrate concepts covered in CSE 3320.

## Process related programs
- [fork.c][01] 		Demonstrates a simple forking of a child process
- [waitpid.c][02]	Demonstrates how to wait on a specific child process and also determine why the child process died
- [exec.c][03]		Fork a child and then call exec to turn the child into an ls process
- [thread.c][11]	Spawn a thread	

## Inter-process communication related programs
- [pipe.c][05]	Open a pipe between two processes and write a string from one to the other
- [pipe_redirect.c][06]	Open a pipe between two processes and redirect stdin and stdout 
- [shared_mem.c][13]	Setup a shared memory segment and read or write using it 
- [memmap.c][16]	Memory map a file and read from it
- [named_listener.c][17]	Create a listener on a named pipe
- [named_sender.c][18]	Create a writer to a named pipe 
- [semaphore.c][19]	Guard a critical seciton using a semaphore

## Signal handling programs
- [sigint.c][07]	Registering a signal handler, with signal(), to catch a ctrl-c (SIGINT)
- [sigint_sigaction_block.c][08]	Registering a signal handler, with sigaction(), to catch a ctrl-c (SIGINT). Also demonstrates masking (blocking) signals
- [sigint_signal_block.c][09]	Registering a signal handler, with signal(), to catch a ctrl-c (SIGINT). Also demonstrates masking (blocking) signals
- [sigqueue_example.c][10]	Send a signal to a process using sigqueue()
- [alarm.c][12]		Set a signal handler for SIGALRM
- [multiple_signals.c][14]	Set a single signal handler for multiple signals 
- [block_signal.c][15]	Block signals with sigprocmask()

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
[09]:https://github.com/CSE3320/Code-Samples/blob/master/sigint_signal_block.c 
[10]:https://github.com/CSE3320/Code-Samples/blob/master/sigqueue_example.c 
[11]:https://github.com/CSE3320/Code-Samples/blob/master/thread.c
[12]:https://github.com/CSE3320/Code-Samples/blob/master/alarm.c
[13]:https://github.com/CSE3320/Code-Samples/blob/master/shared_mem.c
[14]:https://github.com/CSE3320/Code-Samples/blob/master/multiple_signals.c
[15]:https://github.com/CSE3320/Code-Samples/blob/master/block_signals.c
[16]:https://github.com/CSE3320/Code-Samples/blob/master/memmap.c
[17]:https://github.com/CSE3320/Code-Samples/blob/master/named_listener.c
[18]:https://github.com/CSE3320/Code-Samples/blob/master/named_sender.c
[19]:https://github.com/CSE3320/Code-Samples/blob/master/semaphore.c
