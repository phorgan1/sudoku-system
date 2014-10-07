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
    std::cout << "   swordfish: " << b.get_strategy_count("swordfish") << '\n';
    std::cout << "   jellyfish: " << b.get_strategy_count("jellyfish") << '\n';
    std::cout << "   y-wing: " << b.get_strategy_count("y-wing") << '\n';
}

int
main()
{
    const char* tests[]=
    {
	"005803700400206008000070000064020510090307040023060980000080000100402005002705800",
	"340000065000030000007609300200000003703518406400000009002704100000050000160000072",
	"..571..8.2...5.4...8...6..7..2.....491..4..285.....1..4..5...3...8.9...1.6..312..",
	NULL
    };
    for(size_t ctr=0;tests[ctr];ctr++){
	board<sz> *b=new board<sz>(tests[ctr]);
	b->print();
	//b->print_large();
	std::cerr << "the board is " << (b->get_valid()==true?"":"not ") << "valid, with " << b->count() << " clues\n";
	//b->brute_force_check();
	//std::cout << "backed up " << b->get_backed_count() << " times\n";
	b->heuristic_solution();
	b->print();
	b->print_large();
	std::cout << "count(): " << b->count() << '\n';
	std::cout << "get_count(): " << b->count() << '\n';

	if(!b->get_valid()){
	    std::cout << "bad puzzle\n";
	}else if(b->is_solved()){
	    std::cout << "valid solved puzzle\n";
	}else{
	    std::cout << "valid but not solved puzzle\n";
	}
	print_counts(*b);
	//board<sz> *bf=new board<sz>(tests[ctr]);
	//bf->brute_force_solution();
	//bf->print();
    }
    exit(0);
}
