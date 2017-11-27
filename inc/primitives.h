#ifndef PRIMITIVES_H
#define PRIMITIVES_H

typedef struct {
	float x1;
	float y1;
	float x2;
	float y2;
}line;

void dimPhosphor(int amount);
void drawPixel(int x, int y, u8 r, u8 g, u8 b);
void drawLine(int x1, int y1, int x2, int y2, u8 r, u8 g, u8 b, int thicc);
void drawImage(line* shape, int x, int y, float scale, u8 r, u8 g, u8 b, int thicc);

int writeToFile(int fileNumber);
int sleep(int offset, int numFrames);

#endif // PRIMITIVES_H
