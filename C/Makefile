FILE ?= main.c

# Compiler dan Flag
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -D__USE_MINGW_ANSI_STDIO=1
BUILD_DIR = build

.PHONY: all build run clean

all: build run

# Compilation
build: $(FILE)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(FILE) -o build/$(basename $(FILE)).exe

# Run the program
run:
	@echo Running $(basename $(FILE)).exe...
	@build/$(basename $(FILE)).exe
	
# Delete all compiled program in the build folder
clean:
	@if exist build\*.exe del /Q build\*.exe
