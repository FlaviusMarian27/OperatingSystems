#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../../phase1/src/treasure_manager.h"
#include "treasure_hub.h"

volatile sig_atomic_t running = 1;

// Handler pentru listarea tuturor hunt-urilor
void handle_sigusr1(int sig) {
    write(1, "\n[Monitor] Semnal primit: list_hunts\n", 37);

    list_treasure("game1");
    list_treasure("game2");
    list_treasure("game3");
}

// Handler pentru listarea comorilor dintr-un anumit hunt
void handle_sigusr2(int sig) {
    char hunt[100];
    
    int fd = open("../../phase2/src/hub_command.txt",O_RDONLY);
    if(fd < 0){
        write(1, "Monitor: Nu se poate deschide hub_command.txt\n", 47);
        return;
    }

    int bytes_read = read(fd, hunt, sizeof(hunt) - 1);
    if(bytes_read <= 0){
        write(1, "Monitor: Eroare citire din hub_command.txt\n", 44);
        if(close(fd) < 0){
            write(1,"Eroare 1 la inchiderea hun_command.txt!\n",41);
            return;
        }
        return;
    }

    hunt[bytes_read] = '\0';
    hunt[strcspn(hunt, "\n")] = '\0';

    if(close(fd) < 0){
        write(1,"Eroare 2 la inchiderea hun_command.txt!\n",41);
        return;
    }

    list_treasure(hunt);
}

// Handler pentru afisarea detaliilor unei comori
void handle_sigterm(int sig) {
    char buffer[200];
    char hunt[100], treasure[100];

    int fd = open("../../phase2/src/hub_command.txt", O_RDONLY);
    if (fd < 0) {
        write(1, "Monitor: Nu pot deschide hub_command.txt\n", 42);
        return;
    }

    int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        write(1, "Monitor: Eroare citire din hub_command.txt\n", 44);
        if(close(fd) < 0){
            write(1,"Eroare 3 la inchiderea hun_command.txt!\n",41);
            return;
        }
        return;
    }

    buffer[bytes_read] = '\0';
    if(close(fd) < 0){
        write(1,"Eroare 4 la inchiderea hun_command.txt!\n",41);
        return;
    }

    char *newline_pos = strchr(buffer, '\n');
    if (newline_pos == NULL) {
        write(1, "Format incorect in hub_command.txt\n", 35);
        return;
    }

    *newline_pos = '\0';
    strcpy(hunt, buffer);
    strcpy(treasure, newline_pos + 1);
    treasure[strcspn(treasure, "\n")] = '\0';

    view_treasure(hunt, treasure);
}

// Handler pentru oprirea monitorului (SIGINT)
void handle_exit(int sig) {
    write(1, "\n[Monitor] Am primit semnalul de terminare. Inchid...\n", 54);
    running = 0;
}

int main() {
    //Schimbam directorul curent pentru a functiona cu ../hunts/ corect
    if (chdir("../../phase1/src") != 0) {
        perror("Eroare la chdir");
        exit(1);
    }

    struct sigaction sa;// decalram structuraa de tip 'sigaction' pt configurarea handler-ului de semnal
    
    // SIGUSR1 - list_hunts
    sa.sa_handler = handle_sigusr1;//setare functie hadler
    sigemptyset(&sa.sa_mask);//pt nu  a bloca alte semnale in handler
    sa.sa_flags = 0;
    if(sigaction(SIGUSR1, &sa, NULL) == -1){
        perror("Eroare la sigaction SIGUSR1");
        exit(-1);
    }

    // SIGUSR2 - list_treasures
    sa.sa_handler = handle_sigusr2;
    if(sigaction(SIGUSR2, &sa, NULL) == -1){
        perror("Eroare la sigaction SIGUSR2");
        exit(-1);
    }

    // SIGTERM - view_treasure
    sa.sa_handler = handle_sigterm;
    if(sigaction(SIGTERM, &sa, NULL) == -1){
        perror("Eroare la sigaction SIGTERM");
        exit(EXIT_FAILURE);
    }

    // SIGINT or SIGQUIT - opreste programul
    sa.sa_handler = handle_exit;
    if(sigaction(SIGINT, &sa, NULL) == -1){
        perror("Eroare la sigaction SIGINT");
        exit(-1);
    }

    write(1, "\nMonitor: Pornit si in asteptare semnale...\n", 44);

    while (running) {
        pause();
    }

    write(1, "Monitor: Iesire normala.\n", 25);
    return 0;
}