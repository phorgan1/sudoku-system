#include <iostream>
#include <sudoku.h>

const size_t sz=9;

int
main()
{
    const char* tests[]=
    {
	"005803700400206008000070000064020510090307040023060980000080000100402005002705800",
	"340000065000030000007609300200000003703518406400000009002704100000050000160000072",
	"..571..8.2...5.4...8...6..7..2.....491..4..285.....1..4..5...3...8.9...1.6..312..",
	".5..2.38.84.....272...6.......6.7...7.4.8.5.6...4.2.......9...858.....39.79.4..5.",

    };
    for(auto test : tests){
	board<sz> *b=new board<sz>(test);
	b->print();
	std::cerr << "the board is " << (b->get_valid()==true?"":"not ") << "valid, with " << b->count() << " clues\n";
	//b->brute_force_check();
	//std::cout << "backed up " << b->get_backed_count() << " times\n";
	b->heuristic_solution();
	b->print();
	std::cout << "count(): " << b->count() << '\n';

	if(!b->get_valid()){
	    std::cout << "bad puzzle\n";
	}else if(b->is_solved()){
	    std::cout << "valid solved puzzle\n";
	}else{
	    std::cout << "valid but not solved puzzle\n";
	}
	b->print_counts();
	delete b;
    }
    return 0;
}
