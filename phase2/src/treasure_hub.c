#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "treasure_hub.h"

pid_t monitor_pid = -1;

int main( void ){

    int option;

    while(1){
        printf("\n=== Treasure Hub Menu ===\n");
        printf("1. Start monitor\n");
        printf("2. Stop monitor\n");
        printf("3. List hunts\n");
        printf("4. List treasures\n");
        printf("5. View treasure\n");
        printf("6. Exit\n");
        printf("Select: ");
        scanf("%d", &option);

        switch(option){
            case 1:
                if(monitor_pid == -1){
                    monitor_pid = start_monitor();
                    if(monitor_pid > 0){
                        printf("Monitor pornit cu PID: %d\n",monitor_pid);
                    }else{
                        printf("Monitorul deja ruleaza!\n");
                    }
                }
                break;

            case 2:
                if (monitor_pid != -1) {
                    stop_monitor();
                    waitpid(monitor_pid, NULL, 0);
                    monitor_pid = -1;
                }else{
                    printf("Monitorul nu este pornit.\n");
                }
                break;
                
            case 3:

                break;

            case 4:

                break;
                
            case 5:

                break;

            case 6:
                if(monitor_pid != -1){
                    printf("Monitorul este inca activ/pornit! Opreste-l intai!\n");
                }else{
                    printf("La revedere!\n");
                    return 0;
                }
                break;
                
            default:
                printf("Invalid option!");
                break;

        }
    }

    return 0;
}