#!/bin/bash

if [ -z "$1" ]; then
    echo "No directory name provided."
    exit 1
fi

if [ -d "$1" ]; then
    echo "Directory '$1' already exists."
    exit 1
fi

RED='\033[0;31m'
NC='\033[0m'

mkdir "$1"
if [ $? -ne 0 ]; then
    echo "{RED}Error: Failed to create directory '$1'.{NC}"
    exit 1
else
    echo "Directory '$1' created successfully."
fi

touch "$1/main.cpp"
touch "$1/README.md"
echo "No readme content was added" > "$1/README.md"
