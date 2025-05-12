#!/bin/bash

gcc treasure_hub.c \
    start_monitor.c \
    stop_monitor.c \
    list_hunts.c \
    list_treasure.c \
    view_treasure.c \
    calculate_score.c \
    ../../phase1/src/list.c \
    ../../phase1/src/view.c \
    -o p

gcc monitor.c \
    ../../phase1/src/list.c \
    ../../phase1/src/view.c \
    -o monitor

echo "Build complet!"