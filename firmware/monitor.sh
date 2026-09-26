#!/usr/bin/env bash
set -u

DEVICE="/dev/serial/by-id/usb-Espressif_USB_JTAG_serial_debug_unit_90:70:69:03:F6:18-if00"

while true; do
    # Wait for the ESP to enumerate/re-enumerate.
    while [ ! -e "$DEVICE" ]; do
        sleep 0.1
    done

    picocom -b 115200 "$DEVICE"
    status=$?

    # Ctrl+A, Ctrl+X -> normal exit.
    if [ "$status" -eq 0 ]; then
        exit 0
    fi

    # Device probably disappeared during reset/flash.
    sleep 0.1
done
