#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "primitives.h"
#include "font.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)   \
    (byte & 0x80 ? '1' : '0'), \
    (byte & 0x40 ? '1' : '0'), \
    (byte & 0x20 ? '1' : '0'), \
    (byte & 0x10 ? '1' : '0'), \
    (byte & 0x08 ? '1' : '0'), \
    (byte & 0x04 ? '1' : '0'), \
    (byte & 0x02 ? '1' : '0'), \
    (byte & 0x01 ? '1' : '0')

void part1(int offset){
    double scale = 32;
    double scaleVel = -7/105.0;
    for (int i = 0; i < 736; i++){
        dimPhosphor(128);

        char string[8][9];
        char bytes[8];


        for (int j = 0; j < 8; j++){
            int modValue;
            if (i < 380) modValue = (int)(60 * (1 - (i/420)));
            else modValue = 5;

            if (i % modValue == 0){
                int returnVal = fread(&bytes, 1, 8, file);
                if (!returnVal) {
                    printf("ERROR: Couldn't read the file! ;_;");
                    exit(1);
                }
                sprintf(string[j], BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(bytes[j]));
            }
            if (i < 32){
                drawText(string[j], 2, j * 32 * scale + 2, scale, i*8, i*8, i*8, 1);
            }else if (i < 720){
                drawText(string[j], 2, j * 32 * scale + 2, scale, 255, 255, 255, 1);
            }else{
                drawText(string[j], 2, j * 32 * scale + 2, scale, 255-i*8, 255-i*8, 255-i*8, 1);
            }
        }
        
        scale += scaleVel;
        if (scale < 4) scale = 4;
        else if (scale < 8.46) scaleVel += 0.0005;
        writeToFile(i + offset);
    }
    dimPhosphor(255);
}
