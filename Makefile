LIBS=-lSDL -lGLU -lGL

dessinRecursif: dessinRecursif.c
	g++ dessinRecursif.c -o dessinRecursif ${LIBS}
