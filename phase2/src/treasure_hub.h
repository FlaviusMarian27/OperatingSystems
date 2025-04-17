#ifndef TREASURE_HUB_H
#define TREASURE_HUB_H

#include <sys/types.h>
#include "../../phase1/src/treasure_manager.h"

extern pid_t monitor_pid;

pid_t start_monitor();
void stop_monitor();
void list_hunts();
void list_treasures();
void view_treasure();

#endif