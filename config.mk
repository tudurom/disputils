PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

CC = cc
LD = $(CC)

CFLAGS +=  -std=c99 `pkg-config --cflags xcb xcb-randr` -pedantic -Wall -O2
LDFLAGS += -std=c99 `pkg-config --libs xcb xcb-randr`
