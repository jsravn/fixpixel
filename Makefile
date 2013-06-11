all: fixpixel

fixpixel: fixpixel.c
	gcc -O2 -g -Wall --std=gnu99 -lncurses -o fixpixel fixpixel.c

clean:
	rm -f fixpixel
