CC ?= g++
ZIP ?= 7za
PDFLAGS += -march=native
CXXFLAGS += -Wall -Wextra -Wpedantic
LDFLAGS += -lm -lstdc++

VDFLAGS += --leak-check=full --show-leak-kinds=all -s

SRCDIRS = $(sort $(dir $(wildcard src/*/)))
INCDIRS = $(shell find inc -type d)
INC_PARAMS = $(addprefix -I,$(INCDIRS))

EXECUTABLE ?= build/program

ZIPFILE		?= ../zipfile.zip
CPPFILES	= $(wildcard src/**/*.cpp src/*.cpp)

.PHONY: all clean zip run test debug

all: PDFLAGS += -O3
all: $(EXECUTABLE)

clean:
	@rm -f $(ZIPFILE)
	@rm -rf build/
	@rm -rf out/*.csv

zip: clean
	$(ZIP) a $(ZIPFILE) ./*

run: $(EXECUTABLE)
	@./$(EXECUTABLE) $(ARGS)

debug: CXXFLAGS += -g
debug: clean
debug: $(EXECUTABLE)

$(EXECUTABLE): $(CPPFILES)
	@mkdir -p build
	$(CC) $(CXXFLAGS) $(INC_PARAMS) -o $@ $^ $(LDFLAGS) $(PDFLAGS)

valgrind: $(EXECUTABLE)
	valgrind $(VDFLAGS) ./$(EXECUTABLE)
