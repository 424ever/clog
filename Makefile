VERSION = 0.1

IDIR = include
CC = gcc
CFLAGS = -I$(IDIR) -Wall -ansi -Werror
LINKFLAGS = -shared
PREFIX = /usr/local

SRCDIR = src
OBJDIR = obj

LIBS = 

_DEPS = clog.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = clog.o
OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

libclog.so: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LINKFLAGS) $(LIBS)

install: libclog.so
	install include/* $(PREFIX)/include
	install libclog.so $(PREFIX)/lib/libclog-$(VERSION).so
	ln -sf libclog-$(VERSION).so $(PREFIX)/lib/libclog.so

$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean libclog.so install

clean:
	rm -f $(OBJDIR)/*.o *~ core $(IDIR)/*~ libclog.so

