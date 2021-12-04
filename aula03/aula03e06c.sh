#!/bin/bash
for (( i = 0; i <= 3; i++ )); do
    xterm &
done

for i in 1 2 3 4; do
    xterm &
done

i="0"
until (( i>=4 )); do
    xterm &
    i=$(($i+1))
done