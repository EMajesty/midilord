#!/usr/bin/env bash
set -u

DEVICE_GLOB="/dev/serial/by-id/*Espressif*"

while true; do
    DEVICE=""

    while [ -z "$DEVICE" ]; do
        for candidate in $DEVICE_GLOB; do
            if [ -e "$candidate" ]; then
                DEVICE="$candidate"
                break
            fi
        done

        [ -z "$DEVICE" ] && sleep 0.1
    done

    picocom -b 115200 "$DEVICE"
    status=$?

    # Normal picocom exit: Ctrl+A, Ctrl+X
    if [ "$status" -eq 0 ]; then
        exit 0
    fi

    sleep 0.1
done
