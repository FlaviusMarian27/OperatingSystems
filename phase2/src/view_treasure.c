#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "treasure_hub.h"

void view_treasure_signal(){
    if(monitor_pid == -1 ){
        perror("Monitorul nu ruleaza!\n");
        return;
    }

    if(kill(monitor_pid,SIGTERM) == -1){
        perror("Eroare la trimiterea semnalului SIGTERM");
    }
}