fixpixel
========

fixpixel is a simple terminal app for flexing the RGB subpixels in an LCD screen. The theory is that causing rapid on-offs can unstick a stuck pixel or subpixel. I wasn't able to find a free solution (there is a popular java app but it is paid), so I created this for fun.

It uses ncurses to fill a terminal window with RGB colors at 60 frames per second.

Usage
-----

ncurses and developer tools should be installed:

```bash
$ make
$ ./fixpixel
```
