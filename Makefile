LIBS=-lSDL -lGLU -lGL

dessinRecursif: dessinRecursif.c
	g++ dessinRecursif.c -o dessinRecursif ${LIBS}

marchingSquares: marchingSquares.c
	g++ marchingSquares.c -o marchingSquares ${LIBS}
