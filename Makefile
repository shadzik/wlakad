PREFIX = /usr
sbindir = $(PREFIX)/sbin
DESTDIR =
SOURCES = wlaka_chkload.c wlaka_logger.c wlaka_chkpid.c wlakad.c
OBJECTS = wlaka_chkload.o wlaka_logger.o wlaka_chkpid.o wlakad.o
TARGET = wlakad
CC = gcc
CCLD = $(CC)
CFLAGS  = -pipe -Wall -W -O2
LDFLAGS = -Wl,--as-needed
LIBS =
DEL_FILE = rm -f
INSTALL = /usr/bin/install -c

all: Makefile $(TARGET)
$(TARGET):  $(OBJECTS)
	$(CCLD) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

clean:
	$(DEL_FILE) $(OBJECTS) $(TARGET)

$(OBJECTS): $(SOURCES)

install:
	$(INSTALL) $(TARGET) $(DESTDIR)/$(sbindir)
