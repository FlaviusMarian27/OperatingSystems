#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "treasure_hub.h"

void list_treasure_signal(){
    if(monitor_pid == -1 ){
        perror("Monitorul nu ruleaza!\n");
        return;
    }

    if(kill(monitor_pid,SIGUSR2) == -1){
        perror("Eroare la trimiterea semnalului SIGUSR2");
    }
}