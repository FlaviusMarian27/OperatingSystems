#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../phase1/src/treasure_manager.h"  // pentru structura TreasureHunt

#define MAX_USERS 256

typedef struct {
    char username[64];
    int  score;
} ScoreEntry;

void calculate_scores(void) {
    const char *hunts[] = { "game1", "game2", "game3" };
    int num_hunts = sizeof(hunts) / sizeof(hunts[0]);

    for (int h = 0; h < num_hunts; h++) {
        const char *hunt_id = hunts[h];
        printf("\n--- Scoruri pentru %s ---\n", hunt_id);

        // Construim calea catre fisierelee binarre ale hunt ului
        char path[256];
        snprintf(path, sizeof(path),"../phase1/src/%s/treasures.dat",hunt_id);

        int fd = open(path, O_RDONLY);
        if (fd < 0) {
            perror("Eroare la deschiderea fisierului!");
            return;
        }

        ScoreEntry entries[MAX_USERS];
        int n_entries = 0;
        TreasureHunt treasure_hunt;
        while(read(fd,&treasure_hunt,sizeof(treasure_hunt)) == sizeof(treasure_hunt)){
            int found = 0;
            for(int i = 0; i < n_entries; i++){
                if(strcmp(entries[i].username,treasure_hunt.username)){
                    entries[i].score = entries[i].score + treasure_hunt.value;
                    found = 1;
                    break;
                }
            }

            if(found != 0 && n_entries < MAX_USERS){
                strncpy(entries[n_entries].username,treasure_hunt.username,sizeof(entries[n_entries].username) - 1);
                entries[n_entries].username[sizeof(entries[n_entries].username) - 1] = '\0';
                entries[n_entries].score = treasure_hunt.value;
                n_entries++;
            }
        }

        if(close(fd) < 0){
            perror("Eroare la inchiderea fisierului!");
            return;
        }

        for (int i = 0; i < n_entries; i++) {
            printf("User: %s | Score: %d\n",entries[i].username,entries[i].score);
        }
    }

}