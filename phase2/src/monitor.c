#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t running = 1;

void handle_sigusr2(int sig) {
    write(1, "Monitor: Am primit semnalul de terminare (SIGUSR2)!\n",53);
    running = 0;
}

int main() {
    struct sigaction sa;// decalram structuraa de tip 'sigaction' pt configurarea handler-ului de semnal
    sa.sa_handler = handle_sigusr2;//setare functie hadler
    sigemptyset(&sa.sa_mask);//pt nu bloca alte semnale in handler
    sa.sa_flags = 0;

    //pregatim handlerul pentru semnalul SIGUSR2
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Eroare la sigaction");
        exit(EXIT_FAILURE);
    }

    write(1, "Monitor: Pornit si in asteptare semnale...\n", 44);

    // Ruleaza pana la semnalul SIGUSR2
    while (running) {
        pause();
    }

    write(1, "Monitor: Iesire normala.\n", 25);
    return 0;
}
