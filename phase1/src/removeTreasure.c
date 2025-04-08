#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "treasure_manager.h"

void remove_treasure(const char *hunt_id, const char *treasure_id){
    
    char temp_path[256];
    snprintf(temp_path,sizeof(temp_path),"../hunts/%s/treasures_temp.txt", hunt_id);

    char log_path[256];
    snprintf(log_path,sizeof(log_path),"../hunts/%s/logged_hunt", hunt_id);

    char original_file_path[256];
    snprintf(original_file_path,sizeof(original_file_path),"../hunts/%s/treasures.txt", hunt_id);
    
    int input_fd = open(original_file_path,O_RDONLY);
    if(input_fd < 0){
        perror("Eroare la deschidere la treasure.txt!\n");
        exit(-1);
    }

    int output_fd = open(temp_path,O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        perror("Eroare la crearea fisierului temporar");
        close(input_fd);
        exit(-1);
    }

    char character;
    char line[512];

    int index = 0;
    int found = 0;

    while(read(input_fd,&character,1) == 1){
        line[index++] = character;


        if (character == '\n') {
            line[index] = '\0';

            // extragere id
            char current_id[32];
            int index2 = 0;
            while (line[index2] != ',' && line[index2] != '\0' && index2 < (int)sizeof(current_id) - 1) {
                current_id[index2] = line[index2];
                index2 = index2 + 1;
            }
            current_id[index2] = '\0';

            if (strcmp(current_id, treasure_id) == 0) {
                found = 1; // linia cautata, nu o scriem
            } else {
                write(output_fd, line, strlen(line));
            }

            index = 0;
        }

        if (index >= sizeof(line) - 1){
            index = 0; // pt overflow
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
            char log_entry[256];
            int log_len = snprintf(log_entry, sizeof(log_entry), "REMOVE %s\n", treasure_id);
            write(log_fd, log_entry, log_len);
            if( close(log_fd) < 0 ){
                perror("Eroare la inchiderea logged_hunt!\n");
                exit(-1);
            }
        }

    }else{
        unlink(temp_path); // stergere fisier temporar
        write(1, "Treasure nu a fost gasit!\n", 27);
    }
}