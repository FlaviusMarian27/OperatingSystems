#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
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
    write(1, "\n[Monitor] Introdu id-ul hunt-ului: ", 37);
    scanf("%s", hunt);

    list_treasure(hunt);
}

// Handler pentru afisarea detaliilor unei comori
void handle_sigterm(int sig) {
    char hunt[100]; 
    char treasure[100];

    write(1, "\n[Monitor] Hunt id: ", 21);
    scanf("%s", hunt);

    write(1, "Treasure id: ", 14);
    scanf("%s", treasure);

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
    sigemptyset(&sa.sa_mask);//pt nu bloca alte semnale in handler
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

    write(1, "Monitor: Pornit si in asteptare semnale...\n", 44);

    // Ruleaza pana la semnalul SIGUSR2
    while (running) {
        pause();
    }

    write(1, "Monitor: Iesire normala.\n", 25);
    return 0;
}
