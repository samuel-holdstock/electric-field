CC = g++
CFLAGS = -Wall -g

all: Electric_Field

Electric_Field: Electric_Field.cpp
	$(CC) $(CFLAGS) -o $@ $^