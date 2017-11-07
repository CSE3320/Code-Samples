#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{

  struct timeval begin;
  struct timeval end;

  gettimeofday( &begin, NULL );

  sleep(5);

  gettimeofday( &end, NULL );

  int time_duration = ( ( end.tv_sec - begin.tv_sec ) * 1000000 + ( end.tv_usec - begin.tv_usec ) );

  printf("Duration: %d\n", time_duration );

  return 0;
}

