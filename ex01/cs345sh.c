/*Athena Grigoraki
csd4109*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h> /*gia na parw path max(chars in path name)*/
#include <assert.h>
#include <sys/wait.h>

#define TRUE 1

char* type_prompt(){

    char directory[PATH_MAX];
    char *user=getlogin();
    if (user == NULL){
        printf("null user\n");
    }
    char* path=getcwd(directory,sizeof(directory));
    if (path == NULL){
        printf("null path\n");
    }

    printf("\n%s@cs345sh%s/$", user,path );
}

int redirection(int size,char *array[],int index,char **filename){ /*gets string and splits in tokens, saves in array*/
    int i=0;
    char *ptr;
    int n=0;
   // printf("size is: %d\n", size);
    for(i; i<size; i++){
        if(array[i] != NULL){
//            printf("array in red: %s\n", array[i]);
//            if(strcmp(array[i],">") == 0){
//                index=1;
//            }
//            else if(strcmp(array[i],">>") == 0){
//                index=2;
//            }else if(strcmp(array[i], "<") == 0){
//                index=3;
//            }
            ptr= strchr(array[i], '>'); /*position where > is in*/
            if(strchr(array[i], '>')){
                index=1;
               // printf("1o velaki");
            }else if(strchr(array[i], '<')){
                ptr=strchr(array[i], '<');
                index=3;
            }
            if(ptr != NULL){ /*if > is found then look on the next position to see if there is >*/
                if(index==1 && *(ptr + 1) == '>'){
                    index=2;
                  //  printf("2o velaki");
                }

                    if (strlen(array[i]) <= 2) { /*edw mpainei mono ama vrei velaki kai prepei na einai mexri 2 ta velakia */
                    int j = 0;

                        for (j = i; j < size - 1; j++) { /*vgazei to velaki/a kai kai pigainei kateutheian sto onoma tou arxeiou gia na graftei ekei to apotelesma tis entolis*/
                           // printf("%d\n", j);
                            array[j] = array[j + 2];
                            array[j + 2] = NULL;

                        }
                        break;
                    }


            }

        }
    }


    //printf("index : %d\n", index);
    return index;
}


char* read_command(char *command){ /*reads input from command line*/
    char* command_x= malloc(80 * sizeof(char));
    size_t length=0;
    //getline(&command_x,&length,stdin);
    fgets(command_x,80, stdin);
    command_x[strcspn(command_x,"\r\n")] = 0; /*h fgets pairnei kai to \n, me auti tin entoli to vgazo*/
    return command_x;
}

void sys_calls(char *s){

    char *array[100];
    char* tokens;
    int size;
    time_t seconds;
    char *filename;
    int index=0;
    int x=0;
    pid_t pid;
    tokens=strtok(s," ");
    array[0]=strdup(tokens);
    int status;
    int i=0;
    while(tokens!= NULL){

        array[i++]=strdup(tokens);
        //printf("%s\n", tokens);
        tokens=strtok(NULL," ");
    }
    size=i;
    array[i]=NULL;


    filename=strdup(array[size-1]);

    x=redirection(size,array,index,&filename);

    if(strcmp(array[0],"exit") == 0){
        exit(EXIT_SUCCESS);
    }else if(strcmp(array[0],"cd") == 0){
       // printf("chdir");
        chdir(array[1]);
    }else if(strcmp(array[0],"time") == 0){
        seconds=time(NULL);
    }else{
       // printf("mpainei stin fork\n");
        pid=fork();
      //  printf("PID : %d\n", pid);
        if(pid > 0){
            wait(NULL);
        }else{

            if(x == 1){
                FILE *fp=fopen(filename, "w+");
             //   printf("file created\n");
             //   printf("filename: %s\n", filename);
                dup2(fileno(fp),fileno(stdout));
                fclose(fp);
            }else if(x == 2){
                FILE *fp=fopen(filename,"a");
                dup2(fileno(fp),fileno(stdout));
                fclose(fp);
            }else if( x == 3){
                FILE *fp=fopen(filename,"r");
                dup2(fileno(fp),fileno(stdin));
                fclose(fp);
            }


            execvp(array[0],array);
        }
    }

}



void main(int argc, char *argv[]) {

    while(TRUE){
    type_prompt();
    char* input;
    char *x;
    x=read_command(input);
    sys_calls(x);



    }
}
