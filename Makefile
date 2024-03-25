CC = gcc

# Compiler flags
# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# -std=c11: Use C11 standard
# -O3: Optimize for speed
CFLAGS = -Wall -Wextra -std=c11 -O3

# Define the directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BUILD_DIR = build
FTD2XX = ftd2xxDriver

ifeq ($(OS),Windows_NT)
	FTD2XX_LIB = $(FTD2XX)/amd64/ftd2xx.lib $(FTD2XX)/i386/ftd2xx.lib
else
	FTD2XX_LIB = $(FTD2XX)/libftd2xx.a
endif

BASE_OBJ = ${OBJ_DIR}/amp.o ${OBJ_DIR}/ams.o ${OBJ_DIR}/frame.o ${OBJ_DIR}/utils.o

# Create the build directory when a prequisite calls for it
$(BUILD_DIR)/%:
	@mkdir $(BUILD_DIR) 2> nul || exit 0

# Compile .c files to .o files when a prerequisite calls for it
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir $(OBJ_DIR) 2> nul || exit 0
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE_DIR) -I$(FTD2XX)


# Default goal
# This will be called when make is called without arguments
.DEFAULT_GOAL := autotests


# Phony targets
# This will prevent make from trying to build a file named after the argument
# of the .PHONY directive
.PHONY: clean autotests simulation usb

# Clean the build directory
clean:
	del /q /f $(OBJ_DIR)\*.*
	rmdir /s /q $(OBJ_DIR)
	del /q /f $(BUILD_DIR)\*.*
	rmdir /s /q $(BUILD_DIR)

# Build the autotests executable
autotests: $(BUILD_DIR)/test_autotests \
		$(BASE_OBJ) \
		test/test_unitaire.c \
		${SRC_DIR}/autotests.c
	$(CC) $(CFLAGS) -o $^ -I$(INCLUDE_DIR)

# Build the simulation executable and initialize data.txt and consigne.txt
simulation: $(BUILD_DIR)/test_sim \
		$(BASE_OBJ) \
		${SRC_DIR}/audisen_sim.c
	$(CC) $(CFLAGS) -o $^ -I$(INCLUDE_DIR)

# Build the usb executable with the ftd2xx library and initialize data.txt
# and consigne.txt
usb: $(BUILD_DIR)/test_usb \
		$(BASE_OBJ) \
		$(SRC_DIR)/usb.c \
		${SRC_DIR}/audisen_usb.c
	$(CC) $(CFLAGS) -DUSB -o $^ -I$(INCLUDE_DIR) -I$(FTD2XX) $(FTD2XX_LIB)