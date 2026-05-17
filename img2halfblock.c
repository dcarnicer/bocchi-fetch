#define STB_IMAGE_IMPLEMENTATION
#include "/tmp/stb_image.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 4) { fprintf(stderr, "Usage: %s <image> <width> <height>\n", argv[0]); return 1; }
    int w, h, ch;
    unsigned char *img = stbi_load(argv[1], &w, &h, &ch, 4);
    if (!img) { fprintf(stderr, "Failed to load image\n"); return 1; }
    int tw = atoi(argv[2]), th = atoi(argv[3]);
    for (int y = 0; y < th; y++) {
        for (int x = 0; x < tw; x++) {
            int sx0 = x * w / tw, sx1 = (x + 1) * w / tw;
            int sy1a = y * 2 * h / (th * 2), sy1b = (y * 2 + 1) * h / (th * 2);
            int sy2a = sy1b, sy2b = (y * 2 + 2) * h / (th * 2);
            if (sy1a >= h) sy1a = h - 1;
            if (sy1b > h) sy1b = h;
            if (sy2a >= h) sy2a = h - 1;
            if (sy2b > h) sy2b = h;

            long r1 = 0, g1 = 0, b1 = 0, a1 = 0, cnt1 = 0;
            for (int sy = sy1a; sy < sy1b; sy++)
                for (int sx = sx0; sx < sx1; sx++) {
                    int idx = (sy * w + sx) * 4;
                    r1 += img[idx]; g1 += img[idx+1]; b1 += img[idx+2]; a1 += img[idx+3]; cnt1++;
                }
            if (cnt1 == 0) { putchar(' '); continue; }

            long r2 = 0, g2 = 0, b2 = 0, a2 = 0, cnt2 = 0;
            for (int sy = sy2a; sy < sy2b; sy++)
                for (int sx = sx0; sx < sx1; sx++) {
                    int idx = (sy * w + sx) * 4;
                    r2 += img[idx]; g2 += img[idx+1]; b2 += img[idx+2]; a2 += img[idx+3]; cnt2++;
                }

            int ar1 = (int)(r1/cnt1), ag1 = (int)(g1/cnt1), ab1 = (int)(b1/cnt1), aa1 = (int)(a1/cnt1);
            int ar2 = 0, ag2 = 0, ab2 = 0, aa2 = 0;
            if (cnt2 > 0) { ar2 = (int)(r2/cnt2); ag2 = (int)(g2/cnt2); ab2 = (int)(b2/cnt2); aa2 = (int)(a2/cnt2); }

            if (aa1 < 64 && aa2 < 64) {
                putchar(' ');
            } else if (aa1 < 64) {
                printf("\033[48;2;%d;%d;%dm \033[0m", ar2, ag2, ab2);
            } else if (aa2 < 64) {
                printf("\033[38;2;%d;%d;%dm\u2580\033[0m", ar1, ag1, ab1);
            } else {
                printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm\u2580\033[0m",
                       ar1, ag1, ab1, ar2, ag2, ab2);
            }
        }
        putchar('\n');
    }
    stbi_image_free(img);
    return 0;
}
