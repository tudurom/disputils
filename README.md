disputils
=========

disputils is a set of utilities for querying information about connected X
displays.

Example
-------

The following script puts the current focused window in the middle of the
current monitor rather than at the center of the root window. Requires
[the wmutils core](https://github.com/wmutils/core/).

```bash
#!/bin/sh

# get display, wid, w/h, border width
MON=$(pfd)
WID=$(pfw)
WW=$(wattr w $WID)
WH=$(wattr h $WID)
BW=$(wattr b $WID)

# get monitor xywh
SW=$(dattr w $MON)
SH=$(dattr h $MON)
SX=$(dattr x $MON)
SY=$(dattr y $MON)

# move the window to the center
wtp $((SW/2 + SX - WW/2 - BW)) $((SH/2 - SY - WH/2 - BW)) $WW $WH $WID
```

Utilities
---------

Here is the current list of utilities:

* `dattr` - get display's attributes (coordinates, size)
* `lsd` - list displays
* `pfd` - print focused display (the display that contains the currently
	focused window)
* `phd` - print hovered display (the display that contains the mouse
	pointer)
* `ppd` - print primary display

Dependencies
------------

disputils relies on the XCB and XCB_randr libraries.

License
-------

All files of the disputils project is released under the [ISC][license] license. See the
`LICENSE` file.

[license]: http://cvsweb.openbsd.org/cgi-bin/cvsweb/src/share/misc/license.template?rev=HEAD

Download, build and install
--------------------

The default `PREFIX` is `/usr/local`. You can override all variables from the
`config.mk` file.

```
$ git clone git://github.com/tudurom/disputils.git && cd disputils
$ make
# make install
```

