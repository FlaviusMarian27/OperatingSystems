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
    snprintf(directory_path, sizeof(directory_path), "../hunts/%s", hunt_id);
    
    if( mkdir(directory_path,0755) == -1 && errno != EEXIST){
        write(1,"Eroare la directory_path!\n",27);
        return;
    }

    //calea catre fisierul treasure.txt
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s/treasures.txt", directory_path);

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

    //verificare id unic
    int check_fd = open(file_path,O_RDONLY);
    if( check_fd >= 0 ){
        char character;
        char lines[512];
        int index = 0;
        while(read(check_fd,&character,1) == 1){
            lines[index++] = character;
            
            if( character == '\n'){
                lines[index++] = '\0';

                char existing_id[32];
                int index2 = 0;
                while(lines[index2] != ',' && lines[index2] != '\0' && index2 < (int)sizeof(existing_id) - 1){
                    existing_id[index2] = lines[index2];
                    index2 = index2 + 1;
                }
                existing_id[index2] = '\0';

                if( strcmp(existing_id,t.ID) == 0 ){
                    write(1, "Eroare: ID-ul exista deja in acest hunt!\n", 42);
                    close(check_fd);
                    return;
                }
                index = 0;
            }

            if (index >= sizeof(lines) - 1){
                index = 0; // pt overflow
            }
        }
        close(check_fd);
    }

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
    snprintf(log_path, sizeof(log_path), "%s/logged_hunt", directory_path);
    
    int log_fd = open(log_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd >= 0) {
        char log_entry[256];
        int log_len = snprintf(log_entry, sizeof(log_entry), "ADD %s\n", t.ID);

        write(log_fd, log_entry, log_len);
        
        if( close(log_fd) < 0 ){
            write(1,"Eroare la inchiderea logged_hunt!\n",35);
            return;
        }
    }

    char target[256];
    snprintf(target, sizeof(target), "../hunts/%s/logged_hunt", hunt_id);

    char linkname[256];
    snprintf(linkname, sizeof(linkname), "../logged_hunt-%s", hunt_id);

    if(symlink(target, linkname) < 0){
        write(1, "Eroare la crearea symbolic link-ului! Probabil ca exista deja!\n", 63);
    }else{
        write(1, "Symbolic link creat cu succes!\n", 31);
    }
}