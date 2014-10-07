#include <iostream>
#include <sudoku.h>

int
main()
{
    const size_t sz=9;
    const size_t numgens=1000000;
    board<sz> b,b2;
    b.generate();
    if(!b.get_valid()){
	std::cout << "bad puzzle\n";
    }else{
	std::cout << "valid puzzle\n";
    }
    time_t first, last;
    first=time(&first);
    for(size_t ctr=0;ctr<numgens;ctr++){
	if(b.generate()==false){
	    std::cout << "generated a bad board\n";
	}
    }
    last=time(&last);
    std::cout << "generated " << numgens << " boards in " << last-first << " seconds\n";
    std::cout << "    thats " << 1000000.0*double(last-first)/numgens << "µs per board\n";
    if(last!=first){
	std::cout << "    or " << numgens/(last-first) << " boards/second\n";
    }

    if(!b.get_valid()){
	std::cout << "bad puzzle\n";
    }else{
	std::cout << "valid puzzle\n";
    }
    b.print();
    b2=b;
    b2.print();
    std::cout << "There are " << b2.count() << " cells set\n";
    
    exit(0);
}
