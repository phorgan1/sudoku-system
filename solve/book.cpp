#include <iostream>
#include <sudoku.h>

const size_t sz=9;
void
print_counts(board<sz> &b)
{
    std::cout << "  counts:\n";
    std::cout << "   naked single: " << b.get_strategy_count("naked single") << '\n';
    std::cout << "   hidden single: " << b.get_strategy_count("hidden single") << '\n';
    std::cout << "   intersection: " << b.get_strategy_count("intersection") << '\n';
    std::cout << "   naked double: " << b.get_strategy_count("naked double") << '\n';
    std::cout << "   hidden double: " << b.get_strategy_count("hidden double") << '\n';
    std::cout << "   naked triple: " << b.get_strategy_count("naked triple") << '\n';
    std::cout << "   hidden triple: " << b.get_strategy_count("hidden triple") << '\n';
    std::cout << "   naked quad: " << b.get_strategy_count("naked quad") << '\n';
    std::cout << "   hidden quad: " << b.get_strategy_count("hidden quad") << '\n';
    std::cout << "   x-wing: " << b.get_strategy_count("x-wing") << '\n';
    std::cout << "   y-wing: " << b.get_strategy_count("y-wing") << '\n';
    std::cout << "   swordfish: " << b.get_strategy_count("swordfish") << '\n';
    std::cout << "   jellyfish: " << b.get_strategy_count("jellyfish") << '\n';
}

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
    for(size_t ctr=0;ctr<vtests.size();ctr++){
	board<sz> *b=new board<sz>(vtests[ctr].tst);
	b->print();
	b->heuristic_solution();
	b->print();
	std::cout << vtests[ctr].name << '\n';
	if(!b->get_valid()){
	    std::cout << "Bad puzzle\n";
	}else if(b->is_solved()){
	    std::cout << "Valid solved puzzle\n";
	}else{
	    b->print_large();
	    std::cout << "Valid but not solved puzzle\n";
	}
	print_counts(*b);
	std::cout << "count: " << b->count() << '\n';
	std::cout << "get_count: " << b->get_count() << '\n';
	std::cout << std::endl;
    }
    exit(0);
}
