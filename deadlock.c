#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex[2];


void * thread_a( void * arg )
{
  while(1) {
  printf("Running A \n");
  pthread_mutex_lock( &mutex[0] );
  pthread_mutex_lock( &mutex[1] );
  usleep(100);
  pthread_mutex_unlock( &mutex[1] );
  pthread_mutex_unlock( &mutex[0] );
  }
}

void * thread_b( void * arg )
{
  while(1)
  {
  printf("Running B \n");
  pthread_mutex_lock( &mutex[1] );
  pthread_mutex_lock( &mutex[0] );
  usleep(100);
  pthread_mutex_unlock( &mutex[0] );
  pthread_mutex_unlock( &mutex[1] );
  }
}

int main()
{
  pthread_t tid[2];

  pthread_create( &tid[0], 0, thread_a, 0 );
  pthread_create( &tid[1], 0, thread_b, 0 );

  pthread_join( tid[0], NULL );
  pthread_join( tid[1], NULL );

  return 0;
}
