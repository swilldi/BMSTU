#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define picture_data_t unsigned char
#define picture_t unsigned char*

void avgColor(picture_data_t res[], picture_data_t *data, int w, int h) {
    long avg[] = { 0, 0, 0, 0 };

    size_t i = 0;
    for (; i + 64 <= w * h * 4; i += 4 * 16) {
        asm volatile(
            "ld4 { v0.16b, v1.16b, v2.16b, v3.16b }, [%[data]]\n"
            "uaddlv h0, v0.16b\n"
            "uaddlv h1, v1.16b\n"
            "uaddlv h2, v2.16b\n"
            "uaddlv h3, v3.16b\n"

            "umov w4, v0.h[0]\n"
            "umov w5, v1.h[0]\n"
            "umov w6, v2.h[0]\n"
            "umov w7, v3.h[0]\n"

            "ldr x9, [%[avg]]\n"
            "add x9, x9, x4\n"
            "str x9, [%[avg]]\n"

            "ldr x9, [%[avg], #8]\n"
            "add x9, x9, x5\n"
            "str x9, [%[avg], #8]\n"

            "ldr x9, [%[avg], #16]\n"
            "add x9, x9, x6\n"
            "str x9, [%[avg], #16]\n"
            
            "ldr x9, [%[avg], #24]\n"
            "add x9, x9, x7\n"
            "str x9, [%[avg], #24]\n"
            : 
            : [data] "r"(data + i), [avg] "r"(avg)
            : "memory", "v0", "v1", "v2", "v3", "x9", "w4", "w5", "w6", "w7"
        );
    }

    for (; i < w * h * 4; i += 4) {
        asm volatile (
            "ldrb w4, [%[data], #0]\n"
            "ldrb w5, [%[data], #1]\n"
            "ldrb w6, [%[data], #2]\n"
            "ldrb w7, [%[data], #3]\n"

            "ldr x9, [%[avg]]\n"
            "add x9, x9, x4\n"
            "str x9, [%[avg]]\n"

            "ldr x9, [%[avg], #8]\n"
            "add x9, x9, x5\n"
            "str x9, [%[avg], #8]\n"

            "ldr x9, [%[avg], #16]\n"
            "add x9, x9, x6\n"
            "str x9, [%[avg], #16]\n"
            
            "ldr x9, [%[avg], #24]\n"
            "add x9, x9, x7\n"
            "str x9, [%[avg], #24]\n"
            : 
            : [data] "r"(data + i), [avg] "r"(avg)
            : "memory", "x9", "w4", "w5", "w6", "w7"
        );
    }

    for (size_t i = 0; i < 4; ++i) {
        asm volatile (
            "ldr x0, [%[color]]\n"
            "udiv x0, x0, %[pixels]\n"
            "str x0, [%[color]]\n"
            :
            : [color] "r"(avg + i), [pixels] "r"((long)(w * h))
            : "memory", "x0", "d0", "d1"
        );
    }

    for (size_t i = 0; i < 4; ++i)
        res[i] = (picture_data_t)avg[i];
}

void setColor(picture_data_t *data, int w, int h, picture_data_t color[]) {
    for (size_t i = 0; i < w * h * 4; i += 4) {
        data[i] = color[0];
        data[i + 1] = color[1];
        data[i + 2] = color[2];
        data[i + 3] = color[3];
    }
}

int main(void) {
    int w, h, channels;
    // picture_data_t *data = stbi_load("imgs/3x3.png", &w, &h, &channels, 4);
    picture_data_t *data = stbi_load("imgs/rdr2.png", &w, &h, &channels, 4);
    // picture_data_t *data = stbi_load("imgs/astin.png", &w, &h, &channels, 4);
    if (!data) {
        printf("Load image error\n");
        return 1;
    }

    printf("size: %d x %d\n", w, h);

    
    picture_data_t res[4];
    avgColor(res, data, h, w);
    setColor(data, w, h, res);
    printf("%d %d %d %d\n", res[0], res[1], res[2], res[3]);

    stbi_write_png("result.png", w, h, 4, data, w * 4);

    stbi_image_free(data);
    return 0;
}