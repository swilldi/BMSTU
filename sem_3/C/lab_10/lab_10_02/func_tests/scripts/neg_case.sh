#!/bin/bash
# IFS=' ' read -ra args < "$2"

if ! ./app.exe < "$1" > /dev/null; then
    exit 0
else
    exit 1
fi