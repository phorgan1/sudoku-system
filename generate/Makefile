CXX=g++
CFLAGS=-ggdb -Wall -Wextra -pedantic -Wconversion -Wfloat-equal -Wshadow -Wmissing-declarations
#CPPFLAGS=
CPPFLAGS=-ggdb -pedantic -Wextra -Wwrite-strings -Wformat=2 -Wall -fstrict-aliasing -O0 -Wstrict-aliasing=3 -std=c++0x -I../include
allbins=generate dig
all: $(allbins)

clean:
	rm -f $(allbins) *.o *~
generate: generate.cpp ../include/sudoku.h
dig: dig.cpp ../include/sudoku.h
