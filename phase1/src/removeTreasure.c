#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "treasure_manager.h"

void remove_treasure(const char *hunt_id, const char *treasure_id){
    
    char original_file_path[256];
    snprintf(original_file_path, sizeof(original_file_path), "../hunts/%s/treasures.dat", hunt_id);

    char temp_path[256];
    snprintf(temp_path, sizeof(temp_path), "../hunts/%s/treasures_temp.dat", hunt_id);

    char log_path[256];
    snprintf(log_path, sizeof(log_path), "../hunts/%s/logged_hunt", hunt_id);
    
    int input_fd = open(original_file_path,O_RDONLY);
    if(input_fd < 0){
        write(1, "Eroare la deschidere treasures.txt!\n", 37);
        return;
    }

    int output_fd = open(temp_path,O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        write(1, "Eroare la crearea fisierului temporar!\n", 40);
        close(input_fd);
        return;
    }

    TreasureHunt treasurehunt;
    int found = 0;
    char remove_user[USERNAME_SIZE];

    while(read(input_fd,&treasurehunt,sizeof(TreasureHunt)) == sizeof(TreasureHunt)){
        if(strcmp(treasurehunt.ID,treasure_id) == 0){
            found = 1; // evitam sa scriem practic linia care ne intereaza
            strcpy(remove_user,treasurehunt.username);
        }else{
            write(output_fd,&treasurehunt,sizeof(TreasureHunt));
        }
    }

    if(close(input_fd) < 0 || close(output_fd) < 0){
        perror("Eroare la inchiderea fisierelor din remove_treasure!\n");
        exit(-1);
    }

    if(found == 1){
        unlink(original_file_path); // stergere fisier original
        rename(temp_path,original_file_path); //redenumire fisier dupa stergere

        
        int log_fd = open(log_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (log_fd >= 0) {

            time_t now = time(NULL);
            struct tm *mod_time = localtime(&now);
            char time_buffer[256];
            strftime(time_buffer, sizeof(time_buffer), "[ %Y-%m-%d %H:%M:%S ]", mod_time);

            char log_entry[256];
            int log_len = snprintf(log_entry, sizeof(log_entry),
            "%s -> User %s | REMOVE %s\n", time_buffer, remove_user,treasure_id);

            write(log_fd, log_entry,log_len);
            if( close(log_fd) < 0 ){
                write(1,"Eroare la inchiderea logged_hunt!\n",35);
                return;
            }

            write(1,"Treasure a fost sters cu succes!\n",34);
        }

    }else{
        unlink(temp_path); // stergere fisier temporar
        write(1, "Treasure nu a fost gasit!\n", 27);
    }
}