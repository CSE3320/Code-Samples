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

// Purpose: Block signals with sigprocmask

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main (int argc, char *argv[])
{
  /*
   Declare a new segset mask we will fill with the
   signals we want to ignore
  */
  sigset_t newmask;

  /*
    Empty out the sigset.  We can't call memset as it's
    not guaranteed to clear the set
  */
  sigemptyset( &newmask );

  /*
    Add SIGINT to the set.  This will allow us to ignore
    any ctrl-c presses
  */
  sigaddset( &newmask, SIGINT );
  sigaddset( &newmask, SIGTSTP );

  /*
    Finally, add the new signal set to our process' control block
    signal mask element.  This will block all SIGINT signals from
    reaching the process
  */
  if( sigprocmask( SIG_BLOCK, &newmask, NULL ) < 0 )
  {
    perror("sigprocmask ");
  }  

  while (1) {
    sleep (1);
  }
  
  return 0;
}

