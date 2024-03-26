CC=gcc
CFLAGS=
LDFLAGS=


FTD2XX=ftd2xxDriver
FTD_LIB=$(FTD2XX)/amd64/ftd2xx.lib

SOURCE_DIR=src
INCLUDE_DIR=include
BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)\obj

OBJS = $(OBJ_DIR)/amp.o $(OBJ_DIR)/ams.o $(OBJ_DIR)/frame.o $(OBJ_DIR)/utils.o

$(BUILD_DIR)/%:
	@mkdir $(BUILD_DIR)\obj

$(OBJ_DIR)%.o: $(SOURCE_DIR)%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_DIR) -I$(FTD2XX)

.PHONY: autotests simulation usb

autotests: $(BUILD_DIR)/autotests \
	$(OBJS) \
	$(OBJ_DIR)/autotests.o \
	$(OBJ_DIR)/test_unitaire.o
	$(CC) -o $^ $(LDFLAGS) -I$(INCLUDE_DIR)

simulation: $(BUILD_DIR)/simulation \
	$(OBJS) \
	$(OBJ_DIR)/audisen_sim.o
	$(CC) -o $^ $(LDFLAGS) -I$(INCLUDE_DIR)

usb: $(BUILD_DIR)/usb \
	 $(OBJS) \
	 $(OBJ_DIR)/usb.o \
	 $(OBJ_DIR)/audisen_usb.o \
	 $(FTD_LIB)
	$(CC) -o $^ $(LDFLAGS) -I$(INCLUDE_DIR) -I$(FTD2XX)