#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

echo "$SCRIPT_DIR"


sudo insmod $SCRIPT_DIR/../../build/linux/x86_64/debug/exp3_export.ko
sudo insmod $SCRIPT_DIR/../../build/linux/x86_64/debug/exp3_call.ko

sudo rmmod exp3_call.ko
sudo rmmod exp3_export.ko
