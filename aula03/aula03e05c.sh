#!/bin/bash
# For all the files in a folder, add prefix "new_" to their names.
# Adding option -r removes the prefix.
(( $# >= 1 )) && (( $# <= 2 )) || { echo "Erro: Deve indicar entre 1-2 argumentos." >&2; exit 1; }
[[ -d $1 ]] || { echo "Erro: O caminho indicado deve ser uma diretoria." >&2; exit 2; }
cd $1
if [[ $2 = "-r" ]]; then
    for f in *; do
        mv "$f" "${f#new_}"
    done
else
    for f in *; do
        mv "$f" "new_$f"
    done
fi