#!/bin/bash

if ! ./app.exe < "$1" > /dev/null; then
    exit 0
else
    exit 1
fi