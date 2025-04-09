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
    strcpy(file_path, "../hunts/");
    strcat(file_path, hunt_id);
    strcat(file_path, "/treasures.txt");

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
    strcpy(header, "Hunt: ");
    strcat(header, hunt_id);
    strcat(header, "\nFile size: ");

    //adaugare dimensiunea fisier
    char size_str[32];
    sprintf(size_str, "%ld", st.st_size);
    strcat(header, size_str);

    strcat(header, " bytes\nLast modified: ");
    strcat(header, time_buffer);
    strcat(header, "\n=======\n");

    write(1,header,strlen(header));
    
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