#!/bin/bash
# Array Sorting

lineCount=0
while read -r line; do
    array[$lineCount]=$line
    lineCount=$((lineCount+1))
done < "$1"

echo "Original Array"
echo ${array[*]}

for (( i = 0; i < ${#array[@]}; i++ )); do
    for (( j = 0; j < ${#array[@]} -i-1; j++ )); do
        if [[ ${array[j]} -gt ${array[$((j+1))]} ]]; then
            # swap
            temp=${array[j]}
            array[$j]=${array[$((j+1))]}
            array[$((j+1))]=$temp
        fi
    done
done

echo "Array in sorted order"
echo ${array[*]}