PREFIX = /usr
MANPREFIX = $(PREFIX)/share/man

CC = cc
LD = $(CC)

CFLAGS +=  `pkg-config --cflags xcb xcb-randr` -std=c99 -pedantic -Wall -O2
LDFLAGS += `pkg-config --libs xcb xcb-randr`
