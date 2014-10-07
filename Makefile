CXX=g++
CFLAGS=-ggdb -Wall -Wextra -pedantic -Wconversion -Wfloat-equal -Wshadow -Wmissing-declarations
#CPPFLAGS=
CPPFLAGS=-ggdb -pedantic -Wextra -Wwrite-strings -Wformat=2 -Wall -fstrict-aliasing -O3 -Wstrict-aliasing=3 -std=c++0x
allbins= guitarscale testit strict-aliasing traitexample bind elfer xkeys xkeynames scales float client stat f2s1 f2s2 f2s3 f2s4
all: $(allbins)

clean: $(allbins)
	rm -f $(allbins) *.o *~
guitarscale: guitarscale.cpp

xkeynames: xkeynames.cpp
	$(CXX) -o xkeynames xkeynames.cpp -lX11
xkeys: xkeys.cpp
	$(CXX) -ggdb -o xkeys xkeys.cpp -lX11
tab: tab.c
	gcc -o tab tab.c
locale_test: locale_test.c
	gcc -o locale_test locale_test.c
foo: foo.c
	gcc -D_GNU_SOURCE -o foo foo.c
bar: bar.cc
	$(CXX) -o bar bar.cc
dllexamp: dllexamp.c
	gcc -o dllexamp --PIC -lasound foo.c
5bit:	5bit.cpp
	$(CXX) -pedantic -Wall -g -o 5bit 5bit.cpp -pg
dumptorrent.o: dumptorrent.cc
	$(CXX) -c -g -o dumptorrent.o dumptorrent.cc
bencode.o: bencode.cc bencode.h
	$(CXX) -c -g -o bencode.o bencode.cc
dumptorrent: dumptorrent.o bencode.o
	$(CXX) -o dumptorrent -g dumptorrent.o bencode.o
test: test.c
	gcc $(CFLAGS) -fstrict-aliasing -O3 -o test test.c
float: float.c
testit: testit.cpp

scalse: scalse.cpp
	$(CXX) $(CPPFLAGS) -L/usr/local/ootbc/build/lib -I/usr/local/ootbc/build/include -o scalse scalse.cpp -ls
daysalive: daysalive.cpp
	$(CXX) $(CPPFLAGS) -lboost_date_time -I/usr/local/ootbc/build/include -o daysalive daysalive.cpp
gccbug: gccbug.c++
	$(CXX) -o test gccbug.c++
f2s1: f2s1.cpp
f2s2: f2s2.cpp
f2s3: f2s3.cpp
f2s4: f2s4.cpp
printbin: printbin.cpp
	$(CXX) -o printbin printbin.cpp
elfer: elfer.cpp elfer.h
