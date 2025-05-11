#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

int monitor_pipe_fd[2];

pid_t start_monitor(){
    pid_t pid;

    if(pipe(monitor_pipe_fd) < 0){
        perror("Eroare la crearea pipe-ului\n");
	    exit(-1);
    }

    pid = fork();

    if( pid < 0 ){
        write(1,"Eroare creeare proces fiu!\n",27);
        exit(-1);
    }

    if(pid == 0){
        close(monitor_pipe_fd[0]); //inchidem capatul de citire
        dup2(monitor_pipe_fd[1], STDOUT_FILENO);//stdout in pipu
        close(monitor_pipe_fd[1]);//nu mai este nevoie de descriptorul original

        execl("./monitor","monitor",NULL);
        write(1,"Eroare la execl monitor!\n",26);
        return 0;
    }

    
    close(monitor_pipe_fd[1]); //inchidem capatul de scriere
    return pid; //returnam pidul monitorului
}