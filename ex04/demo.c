#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#define __NR_dummy_sys 341
#define set_deadlines(pid,deadline,computation_time) syscall(342,pid,deadline,computation_time)

struct d_params {

    unsigned long deadline; /*deadline of process*/
    unsigned long computation_time; /*time needed to complete process*/

};

int main(int argc, char* argv[]){

    int c_pid,i;
    int x=0;
    struct timeval time;

    if(argv[1] != NULL){
        x = atoi(argv[1]);
    }
    else{
        x=2;
    }

    printf("x = %d\n", x);
    gettimeofday(&time,NULL);

    for(i=0; i<x; i++){
        c_pid=fork();
            if ( c_pid > 0){

                printf("LOOP NO. %d\n", i);
                printf("parent process with id: %d and child: %d\n", getpid(), c_pid);


                set_deadlines(c_pid, 100+(time.tv_sec+time.tv_usec), i); /*den leei me ti na thesoume iso to computation time, kai to ethesa me i*/
                wait(NULL);


            }else if( c_pid < 0){
                printf("fork failed. Exiting");
                exit(0);
            }else{
                sleep(i); /*leei na kanei sleep gia kapoio xrono to child process alla den iksera ti ennoei kai ekana sleep*/
                printf("Child process: %d with parent %d\n", getpid(), getppid());


                exit(1);

            }
        }
    sleep(2);
    printf("Back to user level\n");
    return 0;
}
