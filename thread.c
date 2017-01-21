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

/*
  Purpose: demostrate spawing a thread
  To compile: gcc thread.c -lpthread
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
  Small function for our threads to run.  Does nothing.
*/
void *do_nothing(void *ptr)
{
  sleep(10);
  return NULL;
}

int main()
{
  pthread_t do_nothing_thread;
  
  /* 
    Create a thread which executes do_nothing() 
  */
  if(pthread_create(&do_nothing_thread, NULL, do_nothing, NULL )) 
  {
    perror("Error creating thread: ");
    exit( EXIT_FAILURE ); 
  }
  
  if(pthread_join(do_nothing_thread, NULL)) 
  {
    perror("Problem with pthread_join: ");
  }
  return 0;
}
