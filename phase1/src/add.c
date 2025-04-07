#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "treasure_manager.h"

void add_treasure(const char* hunt_id){
    
    //creeare daca nu exista
    if( mkdir("../hunts",0755) == -1 && errno != EEXIST){
        perror("Eroare la mkdir hunts!\n");
        exit(-1);
    }

    //creeaza subdirectorul ex: hunts/game1 -> rezulta o cale completa
    char directory_path[128];
    snprintf(directory_path,sizeof(directory_path),"../hunts/%s",hunt_id);
    if( mkdir(directory_path,0755) == -1 && errno != EEXIST){
        perror("Erroare la directory_path!\n");
        exit(-1);
    }

    //calea catre fisierul treasure.txt
    char file_path[256];
    snprintf(file_path,sizeof(file_path),"%s/treasures.txt",directory_path);

    int fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if( fd < 0 ){
        perror("Erroare la open treasures.txt!\n");
        exit(-1);
    }

    char buffer[128];
    TreasureHunt t;

    write(1, "ID: ", 4);
    read(0, buffer, sizeof(buffer));
    sscanf(buffer, "%s", t.ID);

    write(1, "User: ", 6);
    read(0, buffer, sizeof(buffer));
    sscanf(buffer, "%s", t.username);

    write(1, "Latitude: ", 10);
    read(0, buffer, sizeof(buffer));
    sscanf(buffer, "%f", &t.gps_location.latitude);

    write(1, "Longitude: ", 11);
    read(0, buffer, sizeof(buffer));
    sscanf(buffer, "%f", &t.gps_location.longitude);

    write(1, "Clue: ", 6);
    read(0, buffer, sizeof(buffer));
    sscanf(buffer, " %[^\n]", t.clue_text);

    write(1, "Value: ", 7);
    read(0, buffer, sizeof(buffer));
    sscanf(buffer, "%d", &t.value);


    char line[512];
    int len = snprintf(line, sizeof(line), "%s,%s,%.6f,%.6f,%s,%d\n",
                        t.ID, t.username,
                        t.gps_location.latitude, t.gps_location.longitude,
                        t.clue_text, t.value);

    if (write(fd, line, len) != len) {
        perror("write treasures.txt");
    }
    
    if( close(fd) < 0 ){
        perror("Eroare la inchiderea treasures.txt!\n");
        exit(-1);
    }

    //logged_hunt
    char log_path[256];
    snprintf(log_path, sizeof(log_path), "%s/logged_hunt", directory_path);
    int log_fd = open(log_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd >= 0) {
        char log_entry[256];
        int log_len = snprintf(log_entry, sizeof(log_entry), "ADD %s\n", t.ID);
        write(log_fd, log_entry, log_len);
        if( close(log_fd) < 0 ){
            perror("Eroare la inchiderea logged_hunt!\n");
            exit(-1);
        }
    }
}