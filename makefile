TARGET = out/algorimage
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -Iinc -flto -O3
CHMOD = chmod

.PHONY: default all clean

default: $(TARGET)
all: default
run: all

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJECTS += $(patsubst %.c, %.o, $(wildcard src/*.c))
HEADERS = $(wildcard *.h)
HEADERS += $(wildcard inc/*.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@
	$(CHMOD) +x $@

clean:
	-rm -f *.o
	-rm -f src/*.o
	-rm -f $(TARGET)
	-rm -f out/frames/*.png

run:
	cd out; ./makeMovie.sh
