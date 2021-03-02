
C = gcc
GDB = gdb

CFLAGS = -std=c89 -Wall -Werror -Wfatal-errors

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, objects/%.o, $(SOURCES))

INCLUDE :=
LDFLAGS := -lopengl32 -lgdi32 -shared-libgcc
GDBFLAGS = -cd ./output/

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
	-mkdir objects
	-mkdir output

build: $(OBJECTS) main/main.c main/main.h
	$(C) $(DEFINES) $(OPTIMIZE) $(CFLAGS) $(OBJECTS) $(INCLUDE) -Imain main/main.c -o output/main.exe $(LDFLAGS)

./objects/%.o: ./%.c  ./%.h
	$(C) $(DEFINES) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	-rm ./objects/*.o ./output/*.exe -f
	-del .\\objects\\*.o .\\output\\*.exe /F /Q
	
debug:
	$(GDB) $(GDBFLAGS) main.exe