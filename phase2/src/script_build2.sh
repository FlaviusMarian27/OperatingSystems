#!/bin/bash

gcc treasure_hub.c \
    start_monitor.c \
    stop_monitor.c \
    ../../phase1/src/add.c \
    ../../phase1/src/list.c \
    ../../phase1/src/view.c \
    ../../phase1/src/removeTreasure.c \
    ../../phase1/src/removeHunt.c \
    -o p

gcc monitor.c -o monitor

echo "Build complet!"