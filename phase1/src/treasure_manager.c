#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include "treasure_manager.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Argumente insuficiente!\n");
        exit(-1);
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            perror("Trebuie: ./p add <hunt_id>\n!\n");
            exit(-1);
        }
        add_treasure(argv[2]);
    }else if(strcmp(argv[1],"list") == 0){
        if( argc < 3 ){
            perror("Trebuie: ./p list <hunt_id>\n");
            exit(-1);
        }
        list_treasure(argv[2]);
    }else if(strcmp(argv[1],"view") == 0){
        if( argc < 4 ){
            perror("Trebuie: ./p view <hunt_id> <treasure_id>\n");
            exit(-1);
        }
        view_treasure(argv[2],argv[3]);
    }else if (strcmp(argv[1], "remove_treasure") == 0) {
        if (argc < 4) {
            perror("Usage: ./p remove_treasure <hunt_id> <id>\n");
            exit(-1);
        }
        remove_treasure(argv[2], argv[3]);
    }else{
        perror("Comanda necunoscuta");
        exit(-1);
    }

    return 0;
}