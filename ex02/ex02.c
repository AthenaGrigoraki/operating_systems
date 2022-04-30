#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

static int N=9;
int customers_inside=0;
int customers_outside=0;
static int i=0;
sem_t semaphore;
pthread_mutex_t list_mutex;

void *customer(void *ptr) {

    pthread_mutex_lock(&list_mutex);

    pthread_mutex_unlock(&list_mutex);
    sem_post(&semaphore);
    pthread_exit(NULL);
}

void *chef(void *ptr){
    printf("Chef is ready to receive customers.\n");

    for(i=N; i>0; i--){
        sem_wait(&semaphore); /*wait on a semaphore*/

        pthread_mutex_lock(&list_mutex); /*thread locks mutex*/



        if(((i%3) == 0) && (i!= N)){ /*serves 3 clients at a time and then looks at phone, and also i!=N because the first client should be served*/

            printf("chef checks his phone until next customer arrives\n");
            sleep(5);
        }
        customers_inside++;
        customers_outside--;
        //printf("now cook for customer with ID : %d\n", N);
        printf("Hello customer %d, what would you like?\n",i);
        printf("I would like a giros %d\n", i);
       // printf("customers outside: %d , customers inside: %d\n", customers_outside,customers_inside);
        printf("service ended, customer leaves\n");



        customers_inside--;

        pthread_mutex_unlock(&list_mutex); /*thread unlocks mutex and other threads can lock it*/
    }

    sem_post(&semaphore); /*wakes up a blocked process waiting on a semaphore and increases value*/
    pthread_exit(NULL); /*terminates thread*/

}

int main(int argc, char * argv[]) {

    int tmp_s;
    int i=0;
    customers_outside=N;
    printf("customers outside at start: %d\n", customers_outside);

    pthread_t chef_thread;
    pthread_t customers[N];
    pthread_mutex_init(&list_mutex,NULL); /*creates a mutex*/
    tmp_s=sem_init(&semaphore, 0, 0); /*semaphore is local*/


    pthread_create(&chef_thread, NULL, chef, NULL); /*create thread*/

    for(i=0; i<N; i++){
        pthread_create(&customers[i],NULL,customer,NULL);
    }

    pthread_join(chef_thread, NULL); /*stop and wait for thread to terminate*/
    for(i=0; i<N; i++){
        pthread_join(customers[i],NULL);
    }
    sem_destroy(&semaphore); /*free resources allocated to sem*/
    return 0;
}
