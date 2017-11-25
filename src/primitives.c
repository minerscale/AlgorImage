#include "globals.h"
#include "primitives.h"

// Reduces the brightness of every pixel by amount.
// Slow. use wisley
void dimPhosphor(int amount){
    for (int y = 0; y < DIMENSION_Y; y++){
        for (int x = 0; x < DIMENSION_X; x++){
            if (image[y][x][0] > amount - 1) image[y][x][0] -= amount;
            else image[y][x][0] = 0;
            if (image[y][x][1] > amount - 1) image[y][x][1] -= amount;
            else image[y][x][1] = 0;
            if (image[y][x][2] > amount - 1) image[y][x][2] -= amount;
            else image[y][x][2] = 0;
        }
    }
}

void drawPixel(int x, int y, u8 r, u8 g, u8 b){
    image[y][x][0] = r;
    image[y][x][1] = g;
    image[y][x][2] = b;
}

void drawLine(int x1, int y1, int x2, int y2, u8 r, u8 g, u8 b, int thicc){
    float m = ((float)(y2-y1))/((float)(x2-x1));

    int yBig = (y1 > y2) ? y1 : y2;
    int ySmall = (y1 < y2) ? y1 : y2;

    int xBig = (x1 > x2) ? x1 : x2;
    int xSmall = (x1 < x2) ? x1 : x2;

    if (yBig - ySmall >= xBig - xSmall){
        float x;
        for (float y = ySmall; y < yBig; y++){
            x = ((float)(y-y1) / (float)m) + (float)x1;
            drawPixel((int)x, (int)y, r, g, b);
            if (x+1 < DIMENSION_X && thicc) drawPixel((int)x+1, (int)y, r, g, b);
            if (x-1 > 0 && thicc) drawPixel((int)x-1, (int)y, r, g, b);
        }
    }else{
        float y;
        for (float x = xSmall; x < xBig; x++){
            y = m * (float)(x - x1) + (float)y1;
            drawPixel((int)x, (int)y, r, g, b);
            if (y+1 < DIMENSION_Y && thicc) drawPixel((int)x, (int)y + 1, r, g, b);
            if (y-1 > 0 && thicc) drawPixel((int)x, (int)y - 1, r, g, b);
        }
    }
}
