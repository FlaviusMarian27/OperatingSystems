#ifndef TREASURE_HUB_H
#define TREASURE_HUB_H

#include <sys/types.h>
#include "../../phase1/src/treasure_manager.h"

extern pid_t monitor_pid;
extern int monitor_pipe_fd[2];

pid_t start_monitor();
void stop_monitor();
void list_hunts_signal();
void list_treasure_signal();
void view_treasure_signal();

#endif