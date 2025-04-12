#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "treasure_manager.h"

void view_treasure(const char *hunt_id, const char *treasure_id){

    char file_path[256];
    snprintf(file_path, sizeof(file_path), "../hunts/%s/treasures.dat", hunt_id);

    int fd = open(file_path,O_RDONLY);
    if( fd < 0 ){
        write(1, "Hunt-ul nu exista!\n", 19);
        return;
    }

    int found = 0;
    TreasureHunt treasurehunt;
    while(read(fd,&treasurehunt,sizeof(TreasureHunt)) == sizeof(TreasureHunt)){
        if(strcmp(treasurehunt.ID,treasure_id) == 0 ){
            printf("ID: %s\n", treasurehunt.ID);
            printf("User: %s\n", treasurehunt.username);
            printf("Latitude: %.6f\n", treasurehunt.gps_location.latitude);
            printf("Longitude: %.6f\n", treasurehunt.gps_location.longitude);
            printf("Clue: %s\n", treasurehunt.clue_text);
            printf("Value: %d\n", treasurehunt.value);
            found = 1;
            break;
        }
    }

    if (found == 0) {
        write(1, "Treasure-ul nu a fost gasit!\n", 30);
    }

    if( close(fd) < 0 ){
        write(1,"Eroare la inchiderea fisierului treasure.txt din view!\n",56);
        return;
    }
}
