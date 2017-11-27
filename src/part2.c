#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "primitives.h"
#include "font.h"

line picture[] = {{}, {-1, -1, -1, -1}};

void drawLineSpecial(int x1, int y1, int x2, int y2, u8 r, u8 g, u8 b, int cutoff){

    float m = ((float)(y2-y1))/((float)(x2-x1));
    int yBig = (y1 > y2) ? y1 : y2;
    int ySmall = (y1 < y2) ? y1 : y2;

    int xBig = (x1 > x2) ? x1 : x2;
    int xSmall = (x1 < x2) ? x1 : x2;
    if (yBig - ySmall >= xBig - xSmall){
        float x;
        for (float y = ySmall; y < yBig; y++){
            if (y < cutoff) continue;
            x = ((float)(y-y1) / (float)m) + (float)x1;
            drawPixel((int)x, (int)y, r, g, b);
            drawPixel((int)x+1, (int)y, r/1.2, g/1.2, b/1.2);
            drawPixel((int)x-1, (int)y, r/1.2, g/1.2, b/1.2);
            //drawPixel((int)x+2, (int)y, r/1.5, g/1.5, b/1.5);
            //drawPixel((int)x-2, (int)y, r/1.5, g/1.5, b/1.5);
        }
    }else{
        float y;
        for (float x = xSmall; x < xBig; x++){
            y = m * (float)(x - x1) + (float)y1;
            if (y < cutoff) continue;
            drawPixel((int)x, (int)y, r, g, b);
            drawPixel((int)x, (int)y + 1, r/1.2, g/1.2, b/1.2);
            drawPixel((int)x, (int)y - 1, r/1.2, g/1.2, b/1.2);
            //drawPixel((int)x, (int)y + 2, r/1.5, g/1.5, b/1.5);
            //drawPixel((int)x, (int)y - 2, r/1.5, g/1.5, b/1.5);
        }
    }
}

void drawImageSpecial(line* shape, int x, int y, float scale, u8 r, u8 g, u8 b, int cutoff){
    for (int i = 0;; i++){
        if (shape[i].x1 == -1) break;
        drawLineSpecial((int)((shape[i].x1)*scale + x), (int)((shape[i].y1)*scale + y),
            (int)((shape[i].x2)*scale + x), (int)((shape[i].y2)*scale + y), r, g, b, cutoff);
    }
}


line mountain[] =   {{0, 340, 60, 370}, {60, 370, 150, 320}, {150, 320, 250, 400}, {400, 400, 440, 320},
                    {440, 320, 480, 300}, {480, 300, 600, 400}, {800, 400, 900, 350}, {900, 350, 950, 300},
                    {950, 300, 1024, 360}, {-1,-1,-1,-1}};

void part2(int offset){
    for (int i = 0; i < 30; i++){
        drawText("MACINTOSH", 2, 2, 3, i*(17.0/30), i*(255.0/30), i*(224.0/30), 1);
        offset = writeToFile(offset);
    }

    offset = sleep (offset, 60);

    for (int i = 0; i < 30; i++){
        drawText("PLUS", 160, 105, 3, i*(17.0/30), i*(255.0/30), i*(224.0/30), 1);
        offset = writeToFile(offset);
    }

    offset = sleep (offset, 30);

    
    // m a k e  a  n e o n  g r i d
    for (int i = 0; i < 60; i++){
        for (int j = 0; j < 60; j++){
            // 525, 323 is the focal point

            drawLineSpecial((j - 30) * 256, 1024, 525, 323, 215, 19, 215, ((1024 - i*12.9) > 400) ? (1024 - i*12.9) : 400);
            drawLineSpecial(0, 1024 - ((j)/(j+3.0) * 700.0),
                1024, 1024 - ((j)/(j+3.0) * 700.0), 215, 19, 215, ((1024 - i*12.9) > 400) ? (1024 - i*12.9) : 400);
        }
        drawImageSpecial(mountain, 0, 0, 1, i*(215/30), i*(19/30), i*(215/30), 1024 - i*12.9);
        offset = writeToFile(offset);
    }

    offset = sleep(offset, 60*8);
}
