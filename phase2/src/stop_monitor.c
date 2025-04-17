#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "treasure_hub.h"

void stop_monitor(){
    if (monitor_pid == -1) {
        printf("Monitorul nu este pornit.\n");
        return;
    }

    if(kill(monitor_pid,SIGUSR2) == -1){
        printf("Eroare la trimiterea semnalului catre monitor!\n");
        return;
    }

    printf("Asteptare inchiderea monitorului...\n");

    int status;
    if (waitpid(monitor_pid, &status, 0) == -1) {
        printf("Eroare la waitpid()!\n");
        return;
    }

    if (WIFEXITED(status)) {
        printf("Monitorul s-a închis cu status %d.\n", WEXITSTATUS(status));
    } else {
        printf("Monitorul nu s-a închis normal.\n");
    }
}