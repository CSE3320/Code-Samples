// The MIT License (MIT)
//
// Copyright (c) 2017 Trevor Bakker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// Purpose: Demonstrate sending a signal via sigqueue

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void sighandler(int signo, siginfo_t *info,void *ctx)
{
  printf("SIGINT caught.\n");
  printf("Data passed by siqueue in info->si_int: %d.\n",info->si_int);

  printf("Also can retrieve it in info->si_value.sival_int: %d.\n",
          info->si_value.sival_int);

  exit( EXIT_SUCCESS );
}

int main(void)
{

  struct sigaction act;

  /*
    Set up the signal handler
  */
  act.sa_sigaction = sighandler;

  /*
    Zero out our mask.  We won't be using it, but it's good
    practice to zero it out since we don't know if the compiler 
    did it for us.
  */
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO;

  /*
    Register the handler using sigaction
  */
  if(sigaction(SIGINT,&act,NULL) == -1)
  {
    perror("sigaction: ");
    exit(EXIT_FAILURE);
  }

  /*
    Get my PID so I can send the signal to myself
  */
  pid_t pid = getpid();    

  /*
    sigval is a union that lets us send a pointer or an int
  */
  union sigval my_sigval;

  my_sigval.sival_int = 42;

  printf("Sending myself a SIGINT signal.\n");

  if( sigqueue( pid, SIGINT, my_sigval ) == -1 )
  {
    perror("sigqueue: ");
    exit(EXIT_FAILURE);
  }
  return 0;
}
