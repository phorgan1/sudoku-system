CXX=g++
CFLAGS=-ggdb -Wall -Wextra -pedantic -Wconversion -Wfloat-equal -Wshadow -Wmissing-declarations
#CPPFLAGS=
CPPFLAGS=-ggdb -pedantic -Wextra -Wwrite-strings -Wformat=2 -Wall -fstrict-aliasing -O0 -Wstrict-aliasing=3 -I../include -std=c++11
# use this for less confusing debugging:C
CPPFLAGS+=-fno-inline
CPPFLAGS+=-O3
#LDFLAGS=-lefence
allbins=generate dig
all: $(allbins)

clean:
	rm -f $(allbins) *.o *~ logit
generate: generate.cpp ../include/sudoku.h
dig: dig.cpp ../include/sudoku.h
