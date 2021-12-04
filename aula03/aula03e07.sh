#!/bin/bash
# Calculate the sum of a series of numbers

SCORE="0"
COUNT="0"
SUM="0"
while true; do
    echo -n "Enter your score [0-10] ('q' to quit): "
    read SCORE;
    if (("$SCORE" < "0")) || (("$SCORE" > "10")); then
        echo -n "Try again. "
    elif [[ "$SCORE" == "q" ]]; then
        echo "Sum: $SUM."
        echo "Average: $(($SUM / $COUNT))."
        break
    elif [[ "$SCORE" == "r" ]]; then
        SCORE="0"
        COUNT="0"
        SUM="0"
        echo "Variables have been reset."
    else
        SUM=$((SUM + SCORE))
        COUNT=$((COUNT + 1))
    fi
done
echo "Exiting."