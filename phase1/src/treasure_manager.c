#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include "treasure_manager.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        write(1, "Argumente insuficiente! Trebuie ./p <operation> <hunt_name>\n", 57);
        exit(-1);
    }

    if(strcmp(argv[1], "add") == 0){
        if(argc != 3) {
            write(1, "Trebuie ./p add <hunt_name>\n", 29);
            exit(-1);
        }
        add_treasure(argv[2]);
    }else if(strcmp(argv[1], "list") == 0){
        if(argc != 3) {
            write(1, "Trebuie ./p list <hunt_name>\n", 30);
            exit(-1);
        }
        list_treasure(argv[2]);
    }else if(strcmp(argv[1], "view") == 0){
        if(argc != 4) {
            write(1, "Trebuie ./p view <hunt_name> <treasure_id>\n", 44);
            exit(-1);
        }
        view_treasure(argv[2], argv[3]);
    }else if(strcmp(argv[1], "remove_treasure") == 0){
        if(argc != 4) {
            write(1, "Trebuie ./p remove_treasure <hunt_name> <treasure_id>\n", 55);
            exit(-1);
        }
        remove_treasure(argv[2], argv[3]);
    }else if(strcmp(argv[1], "remove_hunt") == 0){
        if(argc != 3) {
            write(1, "Trebuie ./p remove_hunt <hunt_name>\n", 37);
            exit(-1);
        }
        remove_hunt(argv[2]);
    }else{
        write(1, "Optiune invalida!\n", 19);
        exit(-1);
    }

    return 0;
}