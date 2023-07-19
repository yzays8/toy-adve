CC = g++
TARGET = game
OBJS = main.o engine.o text.o graphic.o data.o
CXXFLAGS = -Wall -Wextra -g -std=c++2b `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

.PHONY: all clean run

all: $(TARGET)

clean:
	rm -rf *.o $(TARGET)

run:
	./$(TARGET)

$(TARGET): $(OBJS) Makefile
	$(CC) $(OBJS) $(LIBS) -o $@

%.o: %.cpp Makefile
	$(CC) $(CXXFLAGS) -c $<
