CC = gcc
PROJECT_MANAGER = project
PRJOCET_BIN = listpost

# FLAGS
BUILD_FLAG = -lm
CFLAG = -Wall
TEST_FLAG = -lcheck -lcheck -lm -lpthread -lrt -lsubunit -std=c99 -lsubunit -lgcov -coverage

BUILD_SRC = ./build/src
BUILD_TEST = ./build/test

BIN_SRC = $(shell find src -name "*.c")
BIN_OBJ = $(patsubst %.c,build/%.o,$(BIN_SRC))

NMAIN_SRC = $(shell find src -name "*.c"  ! -name "main_*" ! -name "main.c")
NMAIN_OBJ = $(patsubst %.c,build/%.o,$(NMAIN_SRC))

./build/src/%.o: ./src/%.c ./src/%.h
	@mkdir -p $(dir $@)
	@$(CC) -g $(CFLAG) -c $< -o $@

./build/src/%.o: ./src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -g $(CFLAG) -c $< -o $@

./build/test/%.o: ./test/%.c
	@mkdir -p $(dir $@)
	@$(CC) -g $(CFLAG) -fprofile-arcs -ftest-coverage -c $< -o $@

all: clear build

clear:
	@rm -rf build/* bin/*

./bin/main: $(NMAIN_OBJ) $(BUILD_SRC)/main.o
	@mkdir -p bin
	@$(CC) $^ -o $@ $(BUILD_FLAG) -O3

build: ./bin/main

build_debug: $(NMAIN_OBJ) $(BUILD_SRC)/main.o
	@mkdir -p bin
	@$(CC) -g $^ -o ./bin/main $(BUILD_FLAG)

run: build_debug
	@./bin/main

debug: build_debug

clean: clear

.PHONY: test clear all adt tc clean vscode build run