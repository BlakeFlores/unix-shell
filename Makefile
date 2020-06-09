CC = g++
CC_Flags = -Wall -Werror -ansi -pednatic
VPATH = ./src
OUTPUT_DIR = ./bin
EXEC = a.out 
SOURCES = $(wildcard src/*.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

all: rshell

rshell: $(OBJECTS)
	@mkdir -p bin
	$(CC) $(CC_FLAGS) $^ -o bin/rshell.out

clean:
	rm -f $(EXEC) $(OBJECTS)
	rm -rf bin

