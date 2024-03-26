CC=gcc
FLAGS=-W -Wall
SRC= $(wildcard *.c)

FTD_LIB=ftd2xx.lib

autotests: amp.c ams.c frame.c utils.c \
	autotests.c \
	test_unitaire.c
	$(CC) -o test_autotests $^ $(FLAGS)

simulation: amp.c ams.c frame.c utils.c \
	audisen_sim.c
	$(CC) -o test_sim $^ $(FLAGS)

usb: amp.c ams.c frame.c utils.c \
	usb.c \
	audisen_usb.c \
	$(FTD_LIB)
	$(CC) -o test_usb $^ $(FLAGS)