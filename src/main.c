#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "miniz.h"
#include "globals.h"
#include "font.h"
#include "primitives.h"

void writeToFile(int fileNumber);

struct stat st = {0};

int main()
{
    if (stat("./frames", &st) == -1) {
        mkdir("./frames", 0700);
    }

    // Initialise ;-;
    for (int y = 0; y < DIMENSION_Y; y++){
        for (int x = 0; x < DIMENSION_X; x++){
            image[y][x][0] = 0;
            image[y][x][1] = 0;
            image[y][x][2] = 0;
        }
    }

    for (int i = 0; i < 60 * 10; i++){
        dimPhosphor(10);

        if (i % 10 == 0){
            drawText("THE QUICK BROWN FOX JUMPS OVER", 0, 0, 1, 255, 255, 255, 0);
            drawText("THE LAZY DOG", 0, 48, 1, 255, 255, 255, 0);
        }
        
        writeToFile(i);
    }

    return 0;
}

void writeToFile(int fileNumber){
    char filename[60];
    sprintf(filename, "./frames/frame_%d.png", fileNumber);
    FILE *fp = fopen(filename, "wb"); // b - binary mode
    size_t png_data_size = 0;
    void *PNG_data = tdefl_write_image_to_png_file_in_memory_ex(image, DIMENSION_X, DIMENSION_Y, 3, &png_data_size, 6, MZ_FALSE);
    fwrite(PNG_data, 1, png_data_size, fp);
    (void) fclose(fp);
}
