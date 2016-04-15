PREFIX = /usr
MANPREFIX = $(PREFIX)/share/man

CC = cc
LD = $(CC)

CFLAGS += -std=c99 -pedantic -Wall -O2
LDFLAGS += -lxcb -lxcb-randr
