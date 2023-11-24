# makefile for server

CC = g++

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++11

INC = -I./include

SRC = $(wildcard ./src/*.cpp)

OBJ = $(SRC:.cpp=.o)

BIN = server

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(BIN)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	rm -f $(OBJ) $(BIN)

fclean: clean

re: fclean all

.PHONY: clean fclean
