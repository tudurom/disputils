disputils
=========

disputils is a set of utilities to query information about connected X
displays.

Download
--------

https://arcetera.moe/dl/rel/disputils-1.2.tar.gz

Example
-------

The following script puts the current focused window in the middle of the
current monitor rather than at the center of the root window.

```bash
#!/bin/sh

# get display, wid, w/h, border width
MON=$(pfd)
WID=$(pfw)
WW=$(wattr w $WID)
WH=$(wattr h $WID)
BW=$(wattr b $WID)

# get monitor xywh
SW=$(dattr -w $MON)
SH=$(dattr -h $MON)
SX=$(dattr -x $MON)
SY=$(dattr -y $MON)

# move the window to the center
wtp $((SW/2 + SX - WW/2 - BW)) $((SH/2 - SY - WH/2 - BW)) $WW $WH $WID
```

Dependencies
------------

* xcb
* xcb_randr

