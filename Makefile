TARGET = spout
OBJS = graphics.o font.o grain.o main.o spout.o

INCDIR = 
CFLAGS = -O3 -Wall -std=c99 -pedantic
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBS = -lpspgum -lpspgu -lpsprtc -lpspaudio -lpng -lm -lz

BUILD_PRX = 1

LIBDIR =
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Template

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
