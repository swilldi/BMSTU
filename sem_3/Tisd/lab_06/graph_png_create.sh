#!/bin/bash

if [ -e tree.dot ]; then
    dot -v -Tpng -o tree.png tree.dot
fi
