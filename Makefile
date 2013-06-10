all: fixpixel

fixpixel: fixpixel.c
	gcc --std=c99 -lncurses -o fixpixel fixpixel.c

clean:
	rm -f fixpixel
