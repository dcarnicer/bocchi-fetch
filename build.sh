#!/bin/bash
# Regenera bocchi.txt desde bocchi.png
# Uso: ./build.sh [ancho]    (altura se calcula como ancho/2 para mantener ratio cuadrado)
# Ej: ./build.sh 50          -> 50x25 caracteres, efectivo 50x50 píxeles
#     ./build.sh 70          -> 70x35 caracteres, efectivo 70x70 píxeles
#     ./build.sh 50 30       -> manual (ratio no cuadrado)

cd "$(dirname "$0")"
gcc -O2 -o img2halfblock img2halfblock.c -lm

W=${1:-50}
if [ -z "$2" ]; then
    H=$((W / 2))
else
    H=${2}
fi

./img2halfblock bocchi.png "$W" "$H" > bocchi.txt
SIZE=$(wc -c < bocchi.txt)
echo "  ${W}×${H} chars → efectivo ${W}×$((H*2)) px (ratio $(echo "scale=3; $W/($H*2)" | bc)) ($SIZE bytes)"
