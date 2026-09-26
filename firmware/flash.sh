#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
WORKSPACE="$SCRIPT_DIR/../../midilord-zephyr-workspace"
BUILD_DIR="$SCRIPT_DIR/build"

cd "$WORKSPACE"

west flash -d "$BUILD_DIR"
