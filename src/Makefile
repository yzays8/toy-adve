CC = g++
TARGET = game
OBJS = main.o engine.o text.o graphic.o data.o sound.o
CXXFLAGS = -Wall -Wextra -std=c++2b `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

.PHONY: all clean run test

all: $(TARGET)

clean:
	rm -rf *.o $(TARGET)

run:
	./$(TARGET) $(FILE)

test:
	./$(TARGET) ../games/sample_game/sample.json

$(TARGET): $(OBJS) Makefile
	$(CC) $(OBJS) $(LIBS) -o $@

%.o: %.cpp Makefile
	$(CC) $(CXXFLAGS) -c $<
