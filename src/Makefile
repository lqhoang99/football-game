CC=g++
CFLAGS= -c -Wall -std=c++11
LDFLAGS=
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
SOURCES = main.cpp Game.cpp Entity.cpp State.cpp PlayState.cpp MenuState.cpp Goal.cpp TeamState.cpp Formation.cpp Team.cpp client.cpp ClientConnection.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main
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
