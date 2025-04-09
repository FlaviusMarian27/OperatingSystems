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
        write(1,"Eroare la mkdir hunts!\n",24);
        return;
    }

    //creeaza subdirectorul ex: hunts/game1 -> rezulta o cale completa
    char directory_path[128];
    strcpy(directory_path, "../hunts/");
    strcat(directory_path, hunt_id);
    
    if( mkdir(directory_path,0755) == -1 && errno != EEXIST){
        write(1,"Eroare la directory_path!\n",27);
        return;
    }

    //calea catre fisierul treasure.txt
    char file_path[256];
    strcpy(file_path, directory_path);
    strcat(file_path, "/treasures.txt");

    int fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if( fd < 0 ){
        write(1,"Eroare la open treasures.txt!\n",31);
        return;
    }

    TreasureHunt t;

    printf("ID: ");
    scanf("%s", t.ID);

    printf("User: ");
    scanf("%s", t.username);

    printf("Latitude: ");
    scanf("%f", &t.gps_location.latitude);

    printf("Longitude: ");
    scanf("%f", &t.gps_location.longitude);

    printf("Clue: ");
    scanf(" %[^\n]", t.clue_text);

    printf("Value: ");
    scanf("%d", &t.value);

    char line[512];
    int len = snprintf(line, sizeof(line), "%s,%s,%.6f,%.6f,%s,%d\n",
                        t.ID, t.username,
                        t.gps_location.latitude, t.gps_location.longitude,
                        t.clue_text, t.value);

    if (write(fd, line, len) != len) {
        perror("write treasures.txt");
    }
    
    if( close(fd) < 0 ){
        write(1,"Eroare la inchiderea treasures.txt!\n",37);
        return;
    }

    //logged_hunt
    char log_path[256];
    strcpy(log_path, directory_path);
    strcat(log_path, "/logged_hunt");
    
    int log_fd = open(log_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd >= 0) {
        char log_entry[256];
        strcpy(log_entry, "ADD ");
        strcat(log_entry, t.ID);
        strcat(log_entry, "\n");
        int log_len = strlen(log_entry);

        write(log_fd, log_entry, log_len);
        
        if( close(log_fd) < 0 ){
            write(1,"Eroare la inchiderea logged_hunt!\n",35);
            return;
        }
    }

    char target[256];
    strcpy(target, "../hunts/");
    strcat(target, hunt_id);
    strcat(target, "/logged_hunt");

    char linkname[256];
    strcpy(linkname, "../logged_hunt-");
    strcat(linkname, hunt_id);

    if(symlink(target, linkname) < 0){
        write(1, "Eroare la crearea symbolic link-ului! Probabil ca exista deja!\n", 63);
    }else{
        write(1, "Symbolic link creat cu succes!\n", 31);
    }
}