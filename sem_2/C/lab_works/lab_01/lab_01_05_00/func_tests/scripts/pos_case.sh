#!/bin/bash

../../app.exe < $1 > result_app.txt
if [ "$(./comparator.sh ./result_app.txt $2)" -eq 0 ]; then
    echo 0
else
    echo 1
fi

