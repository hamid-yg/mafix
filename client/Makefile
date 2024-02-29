# makefile for client

CC = g++

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++11

INC = -I./include -I../common -I../common/Protocols

SRC = $(wildcard ./src/*.cpp ./src/*/*.cpp ../common/*.cpp ../common/Protocols/*.cpp)

OBJ = $(SRC:.cpp=.o)

BIN = _client

TEST_SRC = $(wildcard ./tests/*.cpp)

TEST_OBJ = $(TEST_SRC:.cpp=.o)

TEST_BIN = test_orderbook

LIBS = -I /opt/homebrew/Cellar/criterion/2.4.2/include/ -L /opt/homebrew/Cellar/criterion/2.4.2/lib -lcriterion -pthread

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(BIN)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(TEST_BIN): $(TEST_OBJ) $(filter-out ./src/main.o, $(OBJ))
	$(CC) $(CFLAGS) $(INC) $^ -o $@ $(LIBS)

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(OBJ) $(BIN) $(TEST_OBJ) $(TEST_BIN)

fclean: clean

re: fclean all

.PHONY: clean fclean test
