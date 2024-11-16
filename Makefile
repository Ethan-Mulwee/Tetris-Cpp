LDFLAGS = -lraylib

Tetris: *.cpp 
	g++ -o Tetris *.cpp $(LDFLAGS)

.PHONY: test clean

Debug: *.cpp 
	g++ -o Tetris *.cpp $(LDFLAGS) -g

test: Tetris
	./Tetris

clean:
	rm -f Tetris