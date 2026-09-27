#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
WORKSPACE="$SCRIPT_DIR/../../midilord-zephyr-workspace"
BUILD_DIR="$SCRIPT_DIR/build"

DEVICE="/dev/serial/by-id/usb-Espressif_USB_JTAG_serial_debug_unit_90:70:69:03:F6:18-if00"

echo "Waiting for Midilord..."
until [ -e "$DEVICE" ]; do
    sleep 0.1
done

cd "$WORKSPACE"

west flash \
    -d "$BUILD_DIR" \
    -r esp32 \
    --esp-device "$DEVICE"
