CXX=g++
CFLAGS=-ggdb -Wall -Wextra -pedantic -Wconversion -Wfloat-equal -Wshadow -Wmissing-declarations
#CPPFLAGS=
CPPFLAGS=-ggdb -pedantic -Wextra -Wwrite-strings -Wformat=2 -Wall -fstrict-aliasing -Wstrict-aliasing=3 -std=c++0x -I../include
#CPPFLAGS=-ggdb -fno-inline -pedantic -Wextra -Wwrite-strings -Wformat=2 -Wall -fstrict-aliasing -O3 -Wstrict-aliasing=3 -std=c++0x -I../include
#allbins=solve test daily brute_check brute_solve mine atest book
allbins=daily book test solve brute_check mine atest brute_solve
all: $(allbins)

clean:
	rm -f $(allbins) *.o *~ core* *logit
solve: solve.cpp ../include/sudoku.h
test: test.cpp ../include/sudoku.h
daily: daily.cpp ../include/sudoku.h
book: book.cpp ../include/sudoku.h
brute_check: brute_check.cpp ../include/sudoku.h
brute_solve: brute_solve.cpp ../include/sudoku.h
mine: mine.cpp ../include/sudoku.h
atest: atest.cpp ../include/sudoku.h
