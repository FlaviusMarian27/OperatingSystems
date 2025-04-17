#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

pid_t start_monitor(){
    pid_t pid = fork();

    if( pid < 0 ){
        write(1,"Eroare creeare proces fiu!\n",27);
        return 0;
    }

    if(pid == 0){
        execl("./monitor","monitor",NULL);
        write(1,"Eroare la execl monitor!\n",26);
        return 0;
    }

    return pid; //returnam pidul monitorului
}