#!/bin/bash
[[ $# = 2 ]] || { echo "Erro: Deve indicar 2 argumentos." >&2; exit 1; }

case $1 in
    ?[0-9]) echo "Primeiro argumento válido";;
    *) echo "Primeiro argumento inválido";;
esac

case $2 in
    sec*) echo "Segundo argumento válido";;
    *) echo "Segundo argumento inválido";;
esac