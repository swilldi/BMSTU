#!/bin/bash

echo -n "Lab number: "
read lab_number

echo -n "Tasks count: "
read tasks_count

echo -n "Option number: "
read option_number


cd /Users/dmitriy/BMSTU/sem_2/C/lab_works/
mkdir "lab_"$lab_number
cd "lab_"$lab_number

for i in $(seq $tasks_count)
do
    
    mkdir "lab_0"$lab_number"_0"$tasks_count"_0
