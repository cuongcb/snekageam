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

game:
	$(CC) $(CPPFLAGS) game.cpp -o game
.phony: game

clean:
	$(RM) $(OUTPUT)
	$(RM) $(OUTPUT).dSYM
	$(RM) *.dSYM
	$(RM) game
.phony: clean
