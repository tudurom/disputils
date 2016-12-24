PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

CC = cc
LD = $(CC)

CFLAGS  += -std=c99 -D_XOPEN_SOURCE=700 `pkg-config --cflags xcb xcb-randr` -pedantic -Wall -O2
LDFLAGS += `pkg-config --libs xcb xcb-randr`
