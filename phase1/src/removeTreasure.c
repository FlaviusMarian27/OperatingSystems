#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "treasure_manager.h"

void remove_treasure(const char *hunt_id, const char *treasure_id){
    
    char original_file_path[256];
    snprintf(original_file_path,sizeof(original_file_path),"hunts/%s/treasures.txt", hunt_id);

    char temp_path[256];
    snprintf(temp_path,sizeof(temp_path),"hunts/%s/treasures_temp.txt", hunt_id);

    char log_path[256];
    snprintf(log_path,sizeof(log_path),"hunts/%s/logged_hunt", hunt_id);
    

}