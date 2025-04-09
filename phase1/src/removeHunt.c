#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "treasure_manager.h"

void remove_hunt(const char* hunt_id){
    char directory_path[256];
    strcpy(directory_path, "../hunts/");
    strcat(directory_path, hunt_id);

    char file_path[512];

    DIR *directory = opendir(directory_path);
    if(directory == NULL){
        write(1, "Hunt-ul nu exista!\n", 19);
        return;
    }

    struct dirent* d;

    while((d = readdir(directory)) != NULL){
        if(strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0){
            strcpy(file_path, directory_path);
            strcat(file_path, "/");
            strcat(file_path, d->d_name);

            if(unlink(file_path) < 0){
                write(1, "Eroare la stergerea fisierului!\n", 32);
                closedir(directory);
                return;
            }
        }
    }

    if(closedir(directory) < 0){ 
        write(1,"Eroare la inchiderea directorului!\n",35);
        return;
    }

    if(rmdir(directory_path) < 0){ 
        write(1, "Eroare la stergerea directorului!\n", 34);
        return;
    }

    //stergere link simbolic
    char symlink_path[256];
    strcpy(symlink_path, "../logged_hunt-");
    strcat(symlink_path, hunt_id);

    if (unlink(symlink_path) == 0) {
        write(1, "Symbolic link sters cu succes!\n", 32);
    } else {
        write(1, "Symbolic link inexistent sau deja sters.\n", 42);
    }

    write(1, "Hunt sters cu succes!\n", 22);
}
