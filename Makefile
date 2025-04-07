CC = gcc
TEST = -o test 
SRC = net101.c main.c
PROD = -o ifxplore 

all: test
	./test
	rm test

test: $(SRC)
	$(CC) $(TEST) $(SRC)

production: $(SRC)
	$(CC) $(PROD) $(SRC)

cleanup:
	rm ifxplore
