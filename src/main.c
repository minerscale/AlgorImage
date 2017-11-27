#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "globals.h"
#include "primitives.h"
#include "part1.h"
#include "part2.h"

int main(int argc, char* argv[])
{
    file = fopen(argv[0], "rb");

    // Initialise ;-;
    for (int y = 0; y < DIMENSION_Y; y++){
        for (int x = 0; x < DIMENSION_X; x++){
            image[y][x][0] = 0;
            image[y][x][1] = 0;
            image[y][x][2] = 0;
        }
    }

    //part1(0); // Takes 736 frames
    part2(736);

    return 0;
}
