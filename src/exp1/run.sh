#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

echo "$SCRIPT_DIR"


sudo insmod $SCRIPT_DIR/../../build/linux/x86_64/debug/exp1.ko

sudo rmmod exp1.ko
