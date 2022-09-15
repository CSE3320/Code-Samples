#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  while(1)
  {
    pid_t pid = fork();

    if( pid != 0 )
    {
      sleep(30);
    }
  }

  return 0;
}
