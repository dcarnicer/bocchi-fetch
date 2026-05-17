#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 4) { fprintf(stderr, "Usage: %s <image> <width> <height>\n", argv[0]); return 1; }
    int w, h, ch;
    unsigned char *img = stbi_load(argv[1], &w, &h, &ch, 3);
    if (!img) { fprintf(stderr, "Failed to load image\n"); return 1; }
    int tw = atoi(argv[2]), th = atoi(argv[3]);
    const char *chars = " .:-=+*#%@";
    int clen = 9;
    for (int y = 0; y < th; y++) {
        for (int x = 0; x < tw; x++) {
            int sx = x * w / tw, sy = y * h / th;
            int idx = (sy * w + sx) * 3;
            int r = img[idx], g = img[idx+1], b = img[idx+2];
            int gray = (r + g + b) / 3;
            int c = gray * clen / 256;
            char dith = chars[c];
            printf("\033[38;2;%d;%d;%dm%c\033[0m", r, g, b, dith);
        }
        putchar('\n');
    }
    stbi_image_free(img);
    return 0;
}
