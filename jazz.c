#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

#define NUM_CUSTOMERS 250

int count = 0;
int under_twentyone_count = 0;

pthread_mutex_t mutex;
sem_t doorman;
sem_t count_sema;


void enter_club( int customer_number, int under_21 )
{
  
  if( under_21 )
  {
    pthread_mutex_lock( & mutex );
    under_twentyone_count++;
    pthread_mutex_unlock( & mutex );
  }

  sem_wait ( & count_sema );

  pthread_mutex_lock( & mutex );
  printf("Customer %d %d enters the club\n", customer_number, under_21);
  pthread_mutex_unlock( & mutex );

  count ++;
  sem_post ( & count_sema );
}

void leave_club( int customer_number, int under_21 )
{

  pthread_mutex_lock( & mutex );
  if( under_21 )
    under_twentyone_count--;
  pthread_mutex_unlock( & mutex );

  sem_wait ( & count_sema );
  count --;
  sem_post ( & count_sema );

  pthread_mutex_lock( & mutex );
  printf("Customer %d %d exits the club\n", customer_number, under_21);
  pthread_mutex_unlock( & mutex );
}

void hangout( )
{
  printf("Current under_twentyone count %d\n", under_twentyone_count );
  sem_wait ( & count_sema );
  assert( count < 9 );
  sem_post ( & count_sema );
  sleep( rand() % 30 ) ;
}


void * customer( void * arg )
{
  int customer_number = (int)arg;
  int under_21 = rand() % 2;

  sem_wait( &doorman );

  enter_club( customer_number, under_21 );
  hangout( );
  leave_club( customer_number, under_21 );


  sem_post( &doorman );
  return NULL;
}

int main ( )
{
  pthread_t tid[NUM_CUSTOMERS];
  int i; 

  sem_init( &doorman, 0, 8 );
  sem_init( &count_sema, 0, 1 );

  srand( time( NULL ) );

  for( i = 0; i < NUM_CUSTOMERS; i++ )
  {
    pthread_create( &tid[i], NULL, customer, (void*)i );
  }

  for( i = 0; i < NUM_CUSTOMERS; i++ )
  {
    pthread_join( tid[i], NULL );
  }

  return 0;
}




