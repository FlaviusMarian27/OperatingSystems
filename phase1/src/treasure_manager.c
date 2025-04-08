#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include "treasure_manager.h"

int main() {
    char buffer[128]; 
    char hunt_id[32]; 
    char treasure_id[32];
    int option;

    while (1) {
        write(1, "\n===== Treasure Manager =====\n", 31);
        write(1, "1. Add Treasure\n", 16);
        write(1, "2. List Treasures\n", 18);
        write(1, "3. View Treasure\n", 17);
        write(1, "4. Remove Treasure\n", 19);
        write(1, "5. Remove Hunt\n", 15);
        write(1, "0. Exit\n", 8);
        write(1, "Option: ", 8);

        int n = read(0, buffer, sizeof(buffer));
        buffer[n] = '\0';
        option = atoi(buffer);

        switch (option) {
            case 1:
                write(1, "Hunt ID: ", 9);
                n = read(0, hunt_id, sizeof(hunt_id));
                hunt_id[n] = '\0';
                hunt_id[strcspn(hunt_id, "\n")] = '\0';
                add_treasure(hunt_id);
                break;

            case 2:
                write(1, "Hunt ID: ", 9);
                n = read(0, hunt_id, sizeof(hunt_id));
                hunt_id[n] = '\0';
                hunt_id[strcspn(hunt_id, "\n")] = '\0';
                list_treasure(hunt_id);
                break;

            case 3:
                write(1, "Hunt ID: ", 9);
                n = read(0, hunt_id, sizeof(hunt_id));
                hunt_id[n] = '\0';
                hunt_id[strcspn(hunt_id, "\n")] = '\0';

                write(1, "Treasure ID: ", 13);
                n = read(0, treasure_id, sizeof(treasure_id));
                treasure_id[n] = '\0';
                treasure_id[strcspn(treasure_id, "\n")] = '\0';

                view_treasure(hunt_id, treasure_id);
                break;

            case 4:
                write(1, "Hunt ID: ", 9);
                n = read(0, hunt_id, sizeof(hunt_id));
                hunt_id[n] = '\0';
                hunt_id[strcspn(hunt_id, "\n")] = '\0';

                write(1, "Treasure ID: ", 13);
                n = read(0, treasure_id, sizeof(treasure_id));
                treasure_id[n] = '\0';
                treasure_id[strcspn(treasure_id, "\n")] = '\0';

                remove_treasure(hunt_id, treasure_id);
                break;

            case 0:
                write(1, "La revedere!\n", 14);
                exit(0);

            default:
                write(1, "Optiune invalida!\n", 16);
        }
    }
}