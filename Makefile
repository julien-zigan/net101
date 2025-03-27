CC = gcc
TEST = -o test 
SRC = net101.c main.c
PROD = -o ifnames

all: test
	./test
	rm test

test: $(SRC)
	$(CC) $(TEST) $(SRC)

production: $(SRC)
	$(CC) $(PROD) $(SRC)
