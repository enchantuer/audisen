CC=gcc
CFLAGS=
LDFLAGS=
SRC= $(wildcard *.c)

FTD_LIB=ftd2xx.lib
INCLUDE= $(wildcard *.h)

.PHONY: autotests simulation usb

autotests: amp.c ams.c frame.c utils.c \
	autotests.c \
	test_unitaire.c
	$(CC) -o test_autotests $^ $(LDFLAGS)

simulation: amp.c ams.c frame.c utils.c \
	audisen_sim.c
	$(CC) -o test_sim $^ $(LDFLAGS)

usb: amp.c ams.c frame.c utils.c \
	usb.c \
	audisen_usb.c \
	$(FTD_LIB)
	$(CC) -o test_usb $^ $(LDFLAGS)