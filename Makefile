BUILD_DIR = build
SRC_DIR = src
LD = gcc
OBJ_FILES = $(shell find $(BUILD_DIR)/o -type f -name "*.o")
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
BIN_DIR = $(BUILD_DIR)/bin

.PHONY: all link compile clean run deps

all: run

run: link
	@./run.sh

link: compile
	@echo -----------
	@echo Linking....
	@echo -----------
	$(LD) -o $(BIN_DIR)/main.bin $(OBJ_FILES) $(LFLAGS)
	@echo Done.

compile: $(BUILD_DIR)
	@echo -------------
	@echo Compiling....
	@echo -------------
	@$(MAKE) --no-print-directory -C ./src

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)

deps:
	./deps/deps.sh

clean:
	rm -rf build