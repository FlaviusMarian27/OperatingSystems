#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "treasure_hub.h"

pid_t monitor_pid = -1;
int pipe_fd[2];

void read_from_monitor(){
    char buffer[2048];
    int n = read(pipe_fd[0],buffer, sizeof(buffer)-1);
    if (n > 0){
        buffer[n] = '\0';
        printf("\n--- Raspuns Monitor ---\n%s\n", buffer);
    }else{
        printf("Eroare sau pipe gol la citire.\n");
    }
}

int main( void ){

    int option;

    while(1){
        printf("\n=== Treasure Hub Menu ===\n");
        printf("1. Start monitor\n");
        printf("2. Stop monitor\n");
        printf("3. List hunts\n");
        printf("4. List treasures\n");
        printf("5. View treasure\n");
        printf("6. Score users\n");
        printf("7. Exit\n");
        printf("Select: ");
        scanf("%d", &option);
        while (getchar()!='\n');

        switch(option){
            case 1:
                if(monitor_pid == -1){
                    monitor_pid = start_monitor();
                    if(monitor_pid > 0){
                        printf("Monitor pornit cu PID: %d\n",monitor_pid);
                    }else{
                        printf("Monitorul deja ruleaza!\n");
                    }
                }else{
                    printf("Monitorul deja ruleaza!\n");
                }
                break;

            case 2:
                if (monitor_pid != -1) {
                    stop_monitor();
                    waitpid(monitor_pid, NULL, 0);
                    monitor_pid = -1;
                    close(pipe_fd[0]);
                }else{
                    printf("Monitorul nu este pornit.\n");
                }
                break;
                
            case 3:// List hunts
                if (monitor_pid != -1) {
                    kill(monitor_pid, SIGUSR1);
                    sleep(1);
                    read_from_monitor();
                } else {
                    printf("Monitorul nu este pornit!\n");
                }
                break;

            case 4:// List treasures
                if (monitor_pid != -1) {
                    char hunt[100];
                    printf("Introdu id-ul hunt-ului: ");
                    scanf("%s", hunt);
                    int fd = open("hub_command.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if(fd < 0){
                        perror("Nu se poate deschide hub_command.txt!");
                    }else{
                        write(fd, hunt, strlen(hunt));
                        if(close(fd) < 0){
                            perror("Eroare(4) la inchiderea fisierului hub_command.txt!\n");
                            return 0;
                        }
                        kill(monitor_pid, SIGUSR2);
                        sleep(1);
                        read_from_monitor();
                    }
                }else{
                    printf("Monitorul nu este pornit!\n");
                }
                break;
                
            case 5:// View treasures
                if (monitor_pid != -1) {
                    char hunt[100], treasure[100];
                    printf("Introdu id-ul hunt-ului: ");
                    scanf("%s", hunt);
                    printf("Introdu id-ul comorii: ");
                    scanf("%s", treasure);

                    int fd = open("hub_command.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd < 0) {
                        perror("Nu pot deschide hub_command.txt");
                    } else {
                        dprintf(fd, "%s\n%s", hunt, treasure);//scrierea formatataa intr un descriptor de fisier specificat
                        if(close(fd) < 0){
                            perror("Eroare(5) la inchiderea fisierului hub_command.txt!\n");
                            return 0;
                        }
                        kill(monitor_pid, SIGTERM);
                        sleep(1);
                        read_from_monitor();
                    }
                } else {
                    printf("Monitorul nu este pornit!\n");
                }
                break;
            
            case 6:
                if (monitor_pid != -1) {
                    calculate_scores_with_pipe();
                } else {
                    printf("Monitorul nu este pornit!\n");
                }
                break;

            case 7:
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