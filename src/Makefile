CC=g++ -pthread
CPPFLAGS=-c -g -std=c++14 -Wall -Wextra -pedantic
SOURCES=main.cpp png/lodepng.cpp png/png.cpp Qlearner.cpp Window.cpp config_reader.cpp QMatrix.cpp
OBJECTS=main.o png/lodepng.o png/png.o Qlearner.o Window.o QMatrix.o config_reader.o -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS_RM=main.o png/lodepng.o png/png.o Qlearner.o Window.o QMatrix.o config_reader.o
EXECUTABLE=learner

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS_RM) $(EXECUTABLE)

run: learner
	./learner
 
valgrind: learner
	valgrind --leak-check=full --show-reachable=no ./learner

