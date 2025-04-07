#ifndef TREASURE_MANAGER_H
#define TREASURE_MANAGER_H

#define TREASURE_ID_SIZE 20
#define USERNAME_SIZE 50
#define CLUE_SIZE 256

typedef struct{
    float latitude;
    float longitude;
}GPS;

typedef struct{
    char ID[TREASURE_ID_SIZE];
    char username[USERNAME_SIZE];
    GPS gps_location;
    char clue_text[CLUE_SIZE];
    int value;
}TreasureHunt;

void add_treasure(const char* hunt_id);

void list_treasure(const char* hunt_id);

void view_treasure(const char *hunt_id, const char *treasure_id);

void remove_treasure(const char *hunt_id, const char *treasure_id);

#endif