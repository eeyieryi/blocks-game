# Makefile

CC := cc

PLATFORM_OS ?= LINUX

RAYLIB_SRC_PATH := ./raylib/raylib-5.5/src/
RAYLIB_LIBRARY_PATH := $(RAYLIB_SRC_PATH)
RAYLIB_LIBRARIES := -lraylib -lm -ldl -lpthread
OSX_LIBRARIES := -framework IOKit -framework Cocoa -framework OpenGL

CFLAGS := -Wall -Wextra -ggdb
INCLUDE_PATHS := -I. -I$(RAYLIB_SRC_PATH)

LDFLAGS := -L$(RAYLIB_LIBRARY_PATH)
ifeq ($(PLATFORM_OS), OSX)
	LDFLAGS += $(OSX_LIBRARIES)
endif
LDLIBS := $(RAYLIB_LIBRARIES)

SOURCES := game.c
EXECUTABLE := blocks

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS) $(LDLIBS)
