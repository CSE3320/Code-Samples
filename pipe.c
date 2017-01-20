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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Demonstrate writing from one process to another using a pipe
// gcc pipe.c -o pipe
// To run: ./pipe <string>


int main(int argc, char *argv[])
{
  int pfd[2];
  pid_t cpid;
  char buf;

  assert(argc == 2);

  // Open the pipe
  if ( pipe(pfd) == -1) 
  { 
    perror("pipe"); 
    exit(EXIT_FAILURE); 
  }

  // fork off a child process so we can use the pipe
  // to communicate beytween the two

  cpid = fork();

  if (cpid == -1) 
  { 
    perror("fork"); 
    exit(EXIT_FAILURE); 
  }

  if (cpid == 0) 
  { 
    // Close the write end of the pipe since the child
    // will read from the pipe
    close(pfd[1]);          

    // Block and read from the pipe
    while (read(pfd[0], &buf, 1) > 0)  
    {
      write(STDOUT_FILENO, &buf, 1);
    }

    write(STDOUT_FILENO, "\n", 1);

    // Done reading so close the pipe and exit
    close(pfd[0]);
    _exit(EXIT_SUCCESS);

  } 
  else 
  {           
  
    // Close the read end of the pipe since the parent
    // just writes 
    close(pfd[0]);          

    // Write out the command line argument to the pipe
    write(pfd[1], argv[1], strlen(argv[1]));

    // Done, so close the pipe and wait for the child to exit
    close(pfd[1]);          
    wait(NULL);             
    exit(EXIT_SUCCESS);
  }
}
