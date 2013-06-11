fixpixel
========

fixpixel is a simple terminal app for flexing the RGB subpixels in an LCD
screen. The theory is that causing rapid on-offs can unstick a stuck pixel
or subpixel.

It uses ncurses to fill a terminal window with RGB colors at 60 frames per second.

Usage
-----

ncurses and developer tools should be installed:

```bash
$ make
$ ./fixpixel
```
