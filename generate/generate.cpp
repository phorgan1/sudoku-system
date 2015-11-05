#include <iostream>
#include <sudoku.h>

int
main()
{
    const size_t sz=9;
    const size_t numgens=100000;
    board<sz> b;
    time_t first, last;
    first=time(&first);
    size_t bp=0,gp=0;
    for(size_t ctr=0;ctr<numgens;ctr++){
	b.generate();
	if(!b.get_valid()){
	    bp++;
	}else{
	    gp++;
	}
    }
    last=time(&last);
    std::cout << "generated " << numgens << " boards in " << last-first << " seconds\n";
    std::cout << "  bad puzzles : " << bp << '\n';
    std::cout << "  good puzzles: " << gp << '\n';
    std::cout << "    that's " << 1000000.0*double(last-first)/numgens << "µs per board\n";
    if(last!=first){
	std::cout << "    or " << numgens/(last-first) << " boards/second\n";
    }
    b.print_large();
    return 0;
}
