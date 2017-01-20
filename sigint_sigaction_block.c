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

// Purpose: Register a signal handler with sigaction, not signal(), to catch a SIGINT

void sig_int ( int signum )
{
  printf("Waiting 10 seconds to exit, but setting an alarm for 1 second. \nIf it's blocked it won't fire\n");
  printf("Comment out line 83 to not block alarm.\n");

  alarm(1);

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

  struct sigaction act;

  /*
    Zero out the sigaction struct
  */
  memset (&act, '\0', sizeof(act));

  /*
    Set the handler to use the function handle_signal()
  */
  act.sa_handler = &sig_int;

  /*
    Block every signal during the handler. Comment out the sigfillset line to
    see what happens when we don't block all signals 
  */
  sigfillset(&act.sa_mask);

  /*
    Install the handler and check the return value.
  */
  if (sigaction(SIGINT , &act, NULL) < 0) {
    perror ("sigaction: ");
    return 1;
  }

  printf("Press ctrl-c\n");
  while(1)
  {
    sleep(10);
  }
}
