#!/bin/bash
# For all the files in a folder, show their properties
[[ $# = 1 ]] || { echo "Erro: Deve indicar apenas 1 argumento." >&2; exit 1; }
[[ -d $1 ]] || { echo "Erro: O caminho indicado deve ser uma diretoria." >&2; exit 2; }
for f in $1/*; do
    file "$f"
done