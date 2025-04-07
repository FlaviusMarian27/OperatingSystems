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
    snprintf(file_path,sizeof(file_path),"../hunts/%s/treasures.txt",hunt_id);

    //pt obtinerea informatiilor din fisierul dorit
    struct stat st;
    if(stat(file_path,&st) == -1){
        perror("Eroare la list pt stat!\n");
        exit(-1);
    }

    //st.st_mtime inlocuim pt ca arata secundele
    char time_buffer[256];
    struct tm *mod_time = localtime(&st.st_mtime);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", mod_time);

    char header[512];
    int len = snprintf(header,sizeof(header),
                "Hunt: %s\nFile size: %ld bytes\nLast modified: %s\n=======\n",
                hunt_id,st.st_size,time_buffer);
    write(1,header,len);
    
    //deschidere fisier pt citire valori
    int fd = open(file_path,O_RDONLY);
    if( fd < 0 ){
        perror("Eroare la deschiderea fisierului pentru citire din list!\n");
        exit(-1);
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
        perror("Eroare la inchiderea fisierului pentru citire din list!\n");
        exit(-1);
    }
}