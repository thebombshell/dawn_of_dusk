
C = gcc
GDB = gdb

CFLAGS = -std=c89 -Wall -Werror -Wfatal-errors

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, objects/%.o, $(SOURCES))

INCLUDE :=
LDFLAGS := -shared-libgcc
GDBFLAGS = -cd ./output/

TARGET = WIN32
ifeq ($(TARGET), WIN32)
LDFLAGS = -lgdi32 -shared-libgcc
else ifeq ($(TARGET), LINUX)
LDFLAGS = -pthread -lm -shared-libgcc
endif

DEBUG = FALSE
ifeq ($(DEBUG), TRUE)
DEFINES =
OPTIMIZE = -g
else
DEFINES = -DNDEBUG
OPTIMIZE = -Os -s
endif

all: clean folders build

folders:
	-mkdir depends
	-mkdir objects
	-mkdir output

build: $(DEPENDS) $(OBJECTS) main/main.c main/main.h
	$(C) $(DEFINES) $(OPTIMIZE) $(CFLAGS) $(OBJECTS) $(INCLUDE) -Imain main/main.c -o output/main.exe $(LDFLAGS)


./objects/%.o: ./%.c ./depends/%.d
	$(C) $(DEFINES) $(CFLAGS) $(INCLUDE) -c $< -o $@

DEPENDS := $(SOURCES:%.c=./depends/%.d)

$(DEPENDS):
include $(wildcard $(DEPENDS))

clean:
	-rm ./objects/*.o ./output/*.exe -f
	-del .\\objects\\*.o .\\output\\*.exe /F /Q
	
debug:
	$(GDB) $(GDBFLAGS) main.exe