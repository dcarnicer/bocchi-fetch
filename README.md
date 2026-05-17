# Bocchi Fetch - fastfetch con Bocchi the Rock

Configuración de fastfetch con una imagen de Bocchi renderizada en la terminal.

## Archivos

- `config.jsonc`       - Config de fastfetch (copia a ~/.config/fastfetch/)
- `bocchi.png`         - Imagen PNG original (500x500, fondo transparente)
- `bocchi.txt`         - Imagen pre-renderizada (bloques Unicode ▀ + color ANSI)
- `img2halfblock.c`    - Generador de imagen → texto (con suavizado + transparencia)
- `img2ascii_color.c`  - Generador alternativo (ASCII simple con color)
- `stb_image.h`        - Biblioteca para decodificar PNG/JPEG
- `fastfetch`          - Binario de fastfetch 2.63.1
- `libs/`              - Librerías necesarias (libchafa, libjpeg, etc.)
- `build.sh`           - Script para regenerar bocchi.txt

## Uso

```bash
# Instalar (primera vez)
cp config.jsonc ~/.config/fastfetch/
cp bocchi.txt ~/.config/fastfetch/
cp fastfetch ~/.local/bin/
cp -r libs/* ~/.local/lib/fastfetch/
echo 'export LD_LIBRARY_PATH="$HOME/.local/lib/fastfetch"' >> ~/.bashrc
echo 'fastfetch' >> ~/.bashrc

# Cambiar resolución
./build.sh 70 30       # más detalle
./build.sh 100 50      # máximo detalle (necesita terminal ancha)
```

## Nota sobre imagen real

El protocolo chafa/kitty/sixel no funciona en este entorno (SSH/VM sin display físico).
Si tu terminal soporta kitty, cambia en `config.jsonc`:
```json
"logo": {
    "source": "~/.config/fastfetch/bocchi.png",
    "type": "kitty"
}
```
