#include <pthread.h>
#include <assert.h>

static void * simple_thread(void *) ;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER ; 
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER ; 

int x = 5 ;
int y = 0 ;

int main() 
{
  pthread_t tid = 0 ; 
  int count = 0 ;
  srand (time(NULL)) ;
  int retval = pthread_create(&tid, 0, &simple_thread, 0) ;

  while ( 1 ) 
  {
    x=5;
    if ( x == 5 ) 
    {
      assert( x == 5 ) ; 
    }
    usleep( rand() % 100 ) ;
  }
  return 0 ; 
 }

static void * simple_thread(void * unused)
{
  while ( 1 ) 
  {
    x = 100 ;
    
    usleep( rand() % 100 ) ;
  }
  return NULL ; 
}
