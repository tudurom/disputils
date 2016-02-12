disputils
=========

disputils is a set of utilities to manage multiple monitors with any window
manager that works with wmutils.

Here's a simple example.

The following script puts the current focused window in the middle of the
current monitor rather than at the center of the root window.

```sh
#!/bin/sh

# get display, wid, w/h, border width
MON=$(pfd)
WID=$(pfw)
WW=$(wattr w $WID)
WH=$(wattr h $WID)
BW=$(wattr b $WID)

# get monitor w/h
SW=$(dattr -w $MON)
SH=$(dattr -h $MON)

# move the window to the center
wtp $((SW/2 + SX - WW/2 - BW)) $((SH/2 - SY - WH/2 - BW)) $WW $WH $WID
```

Dependencies
------------

* xrandr
* wmutils/core

Credit
------

These scripts are based off @laserswald's 'backflip', available
[here](https://github.com/laserswald/backflip).

Especially thanks to z3bra and dcat for work on wmutils itself.
