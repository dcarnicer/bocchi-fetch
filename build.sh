#!/bin/bash
# Regenera bocchi.txt desde bocchi.png con la resolución deseada
# Uso: ./build.sh [ancho] [alto]
# Ejemplo: ./build.sh 55 27

W=${1:-55}
H=${2:-27}
cd "$(dirname "$0")"
gcc -O2 -o img2halfblock img2halfblock.c -lm
./img2halfblock bocchi.png "$W" "$H" > bocchi.txt
echo "Generado bocchi.txt a ${W}x${H} (efectivo ${W}x$((H*2)))"
wc -c bocchi.txt
