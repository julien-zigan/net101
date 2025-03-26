CC = gcc
TEST = -o test 
SRC = net101.c 

all: test
	./test
	rm test

test: $(SRC)
	$(CC) $(TEST) $(SRC)
