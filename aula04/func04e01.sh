#!/bin/bash
function imprime_msg() {
    echo "A minha primeira funcao"
    return 0
}

function dados() {
    DATA=$(date | cut -d " " -f 1-3)
    PC=$(hostname)
    Utilizador=$(who | cut -d " " -f 1)
    echo "DATA: $DATA    Utilizador: $Utilizador    PC: $PC"
    return 0
}