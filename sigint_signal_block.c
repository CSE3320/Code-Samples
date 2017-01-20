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

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>

// Purpose: Register a signal handler for ctrl-c (SIGINT) and demonstrate how to block signals

void sig_int ( int signum )
{
  printf("Waiting 10 seconds to exit, but setting an alarm for 1 second. \nIf it's blocked it won't fire\n");
  printf("Comment out line 27 to not block alarm.\n");

  alarm(1);

  sigset_t sigmask;

  /*
    Create a mask set with SIGALRM in it
  */
  sigemptyset(&sigmask);
  sigaddset( &sigmask, SIGALRM);

  /*
    Now block alarm signals in this handler
  */
  sigprocmask( SIG_BLOCK, &sigmask, NULL );

  struct timeval begin;
  struct timeval end;

  gettimeofday( &begin, NULL );
  gettimeofday( &end, NULL );

  int elapsed_time = end.tv_sec - begin.tv_sec;

  /*
    Rather than sleep let's do a busy wait and waste time
  */
  while( elapsed_time < 10 ) 
  {
    usleep(1);
  
    gettimeofday( &end, NULL );
    elapsed_time = ( end.tv_sec + ( end.tv_usec / 1000000 ) ) - 
                   ( begin.tv_sec + ( begin.tv_usec / 1000000 ) ) ;
  }
 
  printf("Alarm didn't fire. Calling exit()\n"); 
  exit( EXIT_SUCCESS );
}

int main(int argc, char* argv[])
{

  /*
    Install the handler and check the return value.
  */
  if (signal(SIGINT , sig_int ) < 0) {
    perror ("sigaction: ");
    return 1;
  }

  printf("Press ctrl-c\n");
  while(1)
  {
    sleep(10);
  }
}
