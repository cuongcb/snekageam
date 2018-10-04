OUTPUT := snake
CPPFILES := main.cpp map.cpp snake.cpp
CPPFLAGS := -g -Wall

CC := g++ -std=gnu++11
RM := rm -vrf

all:
	$(CC) $(CPPFLAGS) $(CPPFILES) -o $(OUTPUT)
.phony: all

run:
	./$(OUTPUT)
.phony: run	

clean:
	$(RM) $(OUTPUT)
	$(RM) $(OUTPUT).dSYM
.phony: clean