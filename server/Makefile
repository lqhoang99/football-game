CC=g++
CFLAGS= -c -Wall -std=c++11
LDFLAGS=
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
SOURCES = server.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=server
BINDIR=/usr/bin

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)
	rm *.o
clean:
	rm main



.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBFLAGS)

.PHONY: all .cpp.o clean
