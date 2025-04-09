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
    strcpy(file_path, "../hunts/");
    strcat(file_path, hunt_id);
    strcat(file_path, "/treasures.txt");

    int fd = open(file_path,O_RDONLY);
    if( fd < 0 ){
        write(1, "Hunt-ul nu exista!\n", 19);
        return;
    }

    char character;
    char line[512];
    int index = 0;
    int found = 0;

    while(read(fd,&character,1) == 1){
        line[index++] = character;

        if( character == '\n'){
            line[index] = '\0';

            //parcurgere linia salvata in tabloul line pt a gasi id-ul
            char current_ID[32];
            int index2 = 0;
            while (line[index2] != ',' && line[index2] != '\0' && index2 < (int)sizeof(current_ID) - 1){
                current_ID[index2] = line[index2];
                index2 = index2 + 1;
            }
            current_ID[index2] = '\0';//id-ul extras din tabloul line

            if( strcmp(current_ID,treasure_id) == 0 ){
                write(1,line,strlen(line));
                found = 1;
                break;
            }
            index = 0; //resetat pt urmatoare linie
        }

        if( index >= sizeof(line) - 1 ){
            index = 0; // pt cazul cand avem depasire de memorie(overflow)
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
