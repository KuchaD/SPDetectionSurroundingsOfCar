NAME=Program
IDIR=include
ODIR=obj
SDIR=src
LDIR=lib
BDIR=bin

CC=g++
CFLAGS=-Wall -ggdb
LIBRARIES=-lpthread -ldlib -lX11

SOURCES=$(wildcard $(SDIR)/*.cpp )
OBJECTS=$(SOURCES:$(SDIR)/%.cpp=$(ODIR)/%.o)
BINARY=$(BDIR)/$(NAME)

print-%: ; @echo $* = $($*)

all: $(BINARY)

run: all
	./$(BINARY)

clean:
	rm -f $(OBJECTS) $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) -iquote$(IDIR) -Iinclude/lib_includes -L$(LDIR) $(OBJECTS) -o $(BINARY) $(LIBRARIES)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -iquote$(IDIR) -c $< -o $@