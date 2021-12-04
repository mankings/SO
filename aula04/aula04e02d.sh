#!/bin/bash
function compare() {
    if [[ $1 -eq $2 ]]; then
        return 0
    elif [[ $1 -gt $2 ]]; then
        return 1
    else
        return 2
    fi
}

echo -n "Type 1st argument: "
read
A=$REPLY
echo -n "Type 2nd argument: "
read
B=$REPLY

compare $A $B
R=$?
if [[ $R -eq "0" ]]; then
    echo "Os números são iguais."
elif [[ $R -eq "1" ]]; then
    echo $A" é o maior."
else
    echo $B" é o maior."
fi