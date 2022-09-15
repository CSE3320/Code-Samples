// The MIT License (MIT)
//
// Copyright (c) 2020 Trevor Bakker
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
//
//
// Purpose: Demonstrate the use of semaphore with a producer / consumers problem.
// In this example there are a number of cashiers to checkout customers.  A customer
// producer will create a random number of customers from 0 to 10 and add them to the 
// line. Cashier threads will check out the customers as they are available.

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define INITIAL_CUSTOMERS 1
#define NUM_CASHIERS 16
#define NONSHARED 1

sem_t customer_checked_out, customers_in_line;    
int customers_waiting = INITIAL_CUSTOMERS ;            

void * CustomerProducer( void * arg ) 
{
  printf( "CustomerProducer created\n" );

  while( 1 )
  {
    // Only produce a new customer if we check out an exiting customer
    sem_wait( &customer_checked_out );

    int new_customers = rand( ) % 10; 
    customers_waiting += new_customers; 

    printf( "Adding %d customers to the line\n", new_customers ); 
    printf( "%d customer waiting in line\n", customers_waiting );

    // Notify the cashiers that we've added a new customer to the lineA
    int i;
    for( i = 0; i < new_customers; i++ )
    {
      sem_post( &customers_in_line );
    }

    // Sleep a little bit so we can read the output on the screen
    sleep( 2 );

  }
}

void * Cashier( void * arg ) 
{

  printf( "Cashier created\n" );

  while( 1 )
  {
    // Wait here for a customer to appear in line
    sem_wait( &customers_in_line );

    customers_waiting --;

    // Check to make sure we haven't reduced the customer count
    // to below 0.  If we have then crash
    assert( customers_waiting >= 0 );

    printf( "Checking out customer. %d customers left in line\n", customers_waiting );

    sem_post( &customer_checked_out );

    // Sleep a little bit so we can read the output on the screen
    sleep( 1 );
  }

}

int main( int argc, char *argv[] ) 
{
  time_t t;

  srand( ( unsigned int ) time( & t ) );

  pthread_t producer_tid;  
  pthread_t cashier_tid [ NUM_CASHIERS ];  

  sem_init( & customer_checked_out, NONSHARED, 0 );  
  sem_init( & customers_in_line,    NONSHARED, INITIAL_CUSTOMERS );   

  pthread_create( & producer_tid, NULL, CustomerProducer, NULL );

  int i;
  for( i = 0; i < NUM_CASHIERS; i++ )
  {
    pthread_create( & cashier_tid[i], NULL, Cashier, NULL );
  }

  pthread_join( producer_tid, NULL );
  for( i = 0; i < NUM_CASHIERS; i++ )
  {
    pthread_join( cashier_tid[i], NULL );
  }

}
