#!/bin/bash

gcc treasure_hub.c start_monitor.c stop_monitor.c -o p

gcc monitor.c -o monitor

echo "Build complet!"