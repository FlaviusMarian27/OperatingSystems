#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "treasure_manager.h"

void list_treasure(const char* hunt_id){

    char file_path[256];
    snprintf(file_path, sizeof(file_path), "../hunts/%s/treasures.txt", hunt_id);

    //pt obtinerea informatiilor din fisierul dorit
    struct stat st;
    if(stat(file_path,&st) == -1){
        write(1, "Eroare! Fisierul treasures.txt nu exista!\n", 43);
        return;
    }

    //st.st_mtime inlocuim pt ca arata secundele
    char time_buffer[256];
    struct tm* mod_time = localtime(&st.st_mtime);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", mod_time);

    char header[512];
    int len = snprintf(header, sizeof(header),
        "Hunt: %s\nFile size: %ld bytes\nLast modified: %s\n=======\n",
        hunt_id, st.st_size, time_buffer);
    write(1, header, len);
    
    //deschidere fisier pt citire valori
    int fd = open(file_path,O_RDONLY);
    if( fd < 0 ){
        write(1, "Eroare la deschiderea treasures.txt pentru citire!\n", 52);
        return;
    }

    //afisare continut
    char character;
    char line[512];
    int index = 0;

    while( read(fd,&character,1) == 1 ){
        line[index++] = character;
        if( character == '\n'){
            write(1,line,index);
            index = 0;
        }

        if( index >= sizeof(line) - 1 ){
            index = 0; // pt cazul cand avem depasire de memorie(overflow)
        }
    }

    if( close(fd) < 0 ){
        write(1, "Eroare la inchiderea fisierului treasures.txt!\n", 48);
        return;
    }
}