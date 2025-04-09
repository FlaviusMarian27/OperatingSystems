#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "treasure_manager.h"

void remove_treasure(const char *hunt_id, const char *treasure_id){
    
    char original_file_path[256];
    strcpy(original_file_path, "../hunts/");
    strcat(original_file_path, hunt_id);
    strcat(original_file_path, "/treasures.txt");

    char temp_path[256];
    strcpy(temp_path, "../hunts/");
    strcat(temp_path, hunt_id);
    strcat(temp_path, "/treasures_temp.txt");

    char log_path[256];
    strcpy(log_path, "../hunts/");
    strcat(log_path, hunt_id);
    strcat(log_path, "/logged_hunt");
    
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
            strcpy(log_entry, "REMOVE ");
            strcat(log_entry, treasure_id);
            strcat(log_entry, "\n");

            write(log_fd, log_entry, strlen(log_entry));
            if( close(log_fd) < 0 ){
                write(1,"Eroare la inchiderea logged_hunt!\n",35);
                return;
            }
        }

    }else{
        unlink(temp_path); // stergere fisier temporar
        write(1, "Treasure nu a fost gasit!\n", 27);
    }
}