#!/bin/bash
# This script checks the existence of a file
[[ $# = 1 ]] || { echo "Erro: Indique um ficheiro." >&2; exit 1; }
echo "Checking..."
if [[ -f $1 ]]
then
    echo "$1 existe e é um ficheiro normal."
    if [[ -w $1 ]]
    then
        echo "O ficheiro tem permissão de escrita."
    fi
    if [[ -x $1 ]]
    then
        echo "O ficheiro tem permissão de execução."
    fi
elif [[ -d  $1 ]]
then
    echo "$1 existe e é uma diretoria."
else
    echo "$1 não existe."
fi
echo "... done."