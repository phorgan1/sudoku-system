#include <iostream>
#include <sudoku.h>

const size_t sz=9;

int
main()
{
    struct test
    {
	std::string tst;
	std::string name;
    };
    std::vector<struct test> vtests={
	{ "...2...341.8.6..............4.5...2.....1.8..7.........2.4.3...6.....1...........", "Royle17-6973"},
	{".......12....35......6...7.7.....3.....4..8..1...........12.....8.....4..5....6..", "Royle17-92" }

    };
    for(auto test : vtests){
	board<sz> *b=new board<sz>(test.tst);
	b->print();
	b->heuristic_solution();
	b->print();
	std::cout << test.name << '\n';
	if(!b->get_valid()){
	    std::cout << "Bad puzzle\n";
	}else if(b->is_solved()){
	    std::cout << "Valid solved puzzle\n";
	}else{
	    b->print_large();
	    std::cout << "Valid but not solved puzzle\n";
	}
	b->print_counts();
	std::cout << "count: " << b->count() << '\n';
	std::cout << std::endl;
	delete b;
    }
    return 0;
}
