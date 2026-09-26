#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
WORKSPACE="$SCRIPT_DIR/../../midilord-zephyr-workspace"
BUILD_DIR="$SCRIPT_DIR/build"

cd "$WORKSPACE"

west build \
    -p auto \
    -d "$BUILD_DIR" \
    -b esp32s3_devkitc/esp32s3/procpu \
    "$SCRIPT_DIR" \
    -- \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

ln -sfn build/compile_commands.json "$SCRIPT_DIR/compile_commands.json"
