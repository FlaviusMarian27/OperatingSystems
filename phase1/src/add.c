#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
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
    snprintf(file_path, sizeof(file_path), "%s/treasures.dat", directory_path);

    int fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if( fd < 0 ){
        write(1,"Eroare la open treasures.txt!\n",31);
        return;
    }

    TreasureHunt treasurehunt;

    printf("ID: ");
    if(scanf("%s", treasurehunt.ID) != 1){
        write(1, "Eroare la citirea ID-ului!\n", 28);
        return;
    }

    printf("User: ");
    if(scanf("%s", treasurehunt.username) != 1){
        write(1, "Eroare la citirea numelui utilizatorului!\n", 43);
        return;
    }

    printf("Latitude: ");
    if(scanf("%f", &treasurehunt.gps_location.latitude) != 1){
        write(1, "Eroare la citirea latitudinii!\n", 32);
        return;
    }

    printf("Longitude: ");
    if(scanf("%f", &treasurehunt.gps_location.longitude) != 1){
        write(1, "Eroare la citirea longitudinii!\n", 33);
        return;
    }

    printf("Clue: ");
    if(scanf(" %[^\n]", treasurehunt.clue_text) != 1){
        write(1, "Eroare la citirea indiciului!\n", 31);
        return;
    }

    printf("Value: ");
    if(scanf("%d", &treasurehunt.value) != 1){
        write(1, "Eroare la citirea valorii comorii!\n", 36);
        return;
    }

    //verificare id unic
    int check_fd = open(file_path, O_RDONLY);
    if (check_fd >= 0){
        TreasureHunt temp;
        while(read(check_fd,&temp,sizeof(TreasureHunt)) == sizeof(TreasureHunt)){
            if(strcmp(temp.ID,treasurehunt.ID) == 0 ){
                write(1, "ID-ul exista deja in acest hunt!\n", 34);
                close(check_fd);
                close(fd);
                return;
            }
        }
        if(close(check_fd) < 0){
            write(1,"Eroare la inchiderea fisierului de check!\n",43);
        }
    }

    if (write(fd, &treasurehunt, sizeof(TreasureHunt)) != sizeof(TreasureHunt)) {
        write(1, "Eroare la scrierea in fisier!\n", 31);
        close(fd);
        return;
    }
    
    if( close(fd) < 0 ){
        write(1,"Eroare la inchiderea treasures.txt!\n",37);
        return;
    }

    //logged_hunt
    char log_path[256];
    snprintf(log_path, sizeof(log_path), "%s/logged_hunt", directory_path);
    
    time_t now = time(NULL);
    struct tm *mod_time = localtime(&now);
    char time_buffer[256];
    strftime(time_buffer, sizeof(time_buffer), "[ %Y-%m-%d %H:%M:%S ]", mod_time);

    int log_fd = open(log_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd >= 0) {
        char log_entry[256];
        int log_len = snprintf(log_entry, sizeof(log_entry), 
        "%s -> User %s | ADD %s\n", time_buffer, treasurehunt.username,treasurehunt.ID);

        write(log_fd, log_entry, log_len);
        
        if( close(log_fd) < 0 ){
            write(1,"Eroare la inchiderea logged_hunt!\n",35);
            return;
        }
    }

    char target[256];
    snprintf(target, sizeof(target), "hunts/%s/logged_hunt", hunt_id);

    char linkname[256];
    snprintf(linkname, sizeof(linkname), "../logged_hunt-%s", hunt_id);

    if (access(linkname, F_OK) == 0) {
        write(1, "Symbolic link deja exista.\n", 28);
    } else {
        if (symlink(target, linkname) == -1) {
            write(1, "Eroare la crearea symbolic link-ului!\n", 39);
        } else {
            write(1, "Symbolic link creat cu succes!\n", 31);
        }
    }
    
}