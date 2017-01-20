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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Open a pipe between two processes and direct STDOUT and STDIN to the pipe
// endpoints

int main(void)
{
  int pfds[2];

  pipe(pfds);

  if (!fork()) {
    close(STDOUT_FILENO);         /* close normal stdout */
    dup(pfds[1]);                 /* make stdout same as pfds[1] */
    close(pfds[0]);               /* we don't need this */
    execlp("ls", "ls", NULL);
  } 
  else 
  {
    close(STDIN_FILENO);          /* close normal stdin */
    dup(pfds[0]);                 /* make stdin same as pfds[0] */
    close(pfds[1]);               /* we don't need this */
    execlp("wc", "wc", "-l", NULL);
  }

  return 0;
}
