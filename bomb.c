#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main ()
{
  while( 1 )
  {
    pid_t pid = fork();
    
    if ( pid == -1 )
    {
      perror("Fork: ");
    }
  }

  return 0;
}


