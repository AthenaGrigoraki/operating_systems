#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define __NR_dummy_sys 341
#define set_deadlines(pid,deadline,computation_time) syscall(342,pid,deadline,computation_time)

struct d_params {

    unsigned long deadline; /*deadline of process*/
    unsigned long computation_time; /*time needed to complete process*/

};

int main(void){

    int c_pid;
    unsigned long y;
    int x;
    int status;
    printf("Trap to kernel level\n");
     /* you should check return value for errors */

     y=set_deadlines(-1, -2, 5);
     printf(" Deadline < 0 .  expected :set failed\n" );
     if (y==0)   printf(" set succeeded\n" );
     else printf("set failed\n\n" );
     printf("----------------------------\n" );
     y=set_deadlines(-1, 5, -2);
     printf(" computation time < 0 . expected: set failed\n" );
     if (y==0)   printf(" set succeeded\n" );
     else printf("set failed\n\n" );
     printf("----------------------------\n" );
     y=set_deadlines(-2345, 5, 10);
     printf("invalid pid . expected: set failed\n");
     if (y==0)   printf(" set succeeded\n" );
     else printf("set failed\n\n" );
     printf("----------------------------\n" );
     y=set_deadlines(-1, 5, 10);
     printf(" Deadline < computation time .  expected :set failed\n" );
     if (y==0)   printf(" set succeeded\n" );
     else printf("set failed\n\n" );
     printf("----------------------------\n" );
     y=set_deadlines(-1, 10, 5);
     printf(" valid set .  expected :set succeeded\n" );
     if (y==0)   printf(" set succeeded\n" );
     else printf("set failed\n\n" );
     printf("----------------------------\n" );


    fflush(stdout);
    c_pid=fork();
    if ( c_pid > 0){


            printf("parent process with id: %d and child: %d\n", getpid(), c_pid);


            set_deadlines(c_pid, 10,5);
            wait(&status);


    }else if( c_pid < 0){
            printf("fork failed. Exiting");
            exit(0);
    }else{
        sleep(5);
        printf("Child process: %d with parent %d\n", getpid(), getppid());

        /*syscall(__NR_dummy_sys, 42);*/
        set_deadlines(-1, 6,3);
        /*printf("computation time: %d\n deadline: %d\n",dparams->computation_time, dparams->deadline);*/

    }
    sleep(2);
    printf("Back to user level\n");
    return 0;
}
