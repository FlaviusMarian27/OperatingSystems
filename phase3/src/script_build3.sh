#!/bin/bash

gcc treasure_hub.c \
    start_monitor.c \
    stop_monitor.c \
    list_hunts.c \
    list_treasure.c \
    view_treasure.c \
    ../../phase1/src/list.c \
    ../../phase1/src/view.c \
    -o treasure_hub

gcc monitor.c \
    ../../phase1/src/list.c \
    ../../phase1/src/view.c \
    -o monitor

echo "Build complet!"