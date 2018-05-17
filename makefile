cc = c++
CFLAGS = -Wall -lncurses -std=c++11 -I$(INCLUDES) -g

IDIR = ./include/
SRCDIR = ./src/

INCLUDES = $(IDIR)

SOURCES = $(SRCDIR)*.cpp\

all:nethack

nethack:$(SOURCES)
	$(cc) $(SOURCES) $(CFLAGS) -o $@

run:
	./nethack

clean:
	rm nethack
