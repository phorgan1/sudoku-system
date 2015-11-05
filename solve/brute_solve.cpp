#include <iostream>
#include <sudoku.h>

const size_t sz=9;
int
main()
{
    struct test
    {
	std::string tst;
	std::string diff;
	std::string name;
	std::string copyright;
    };
    std::vector<struct test> vtests={
#if 0
	{ "....1...349.......7.1624...16....54.3.9...2.1.87....96...1739.2.......352...5....", "1 star", "", "Knight Features"}, // 1288
	{ "....1....49.......7...24...1......4...9...2.1..7....96...17...2........52...5....", "1 star", "", "Knight Features"}, // 184
	{ "...8.1.........43.5............7.8........1...2..3....6......75..34........2..6..", "", "", ""}, // 14904951
	{ "5.......9.2.1...7...8...3...4.......................1.3.....8...6...4.2...9.....5", "", "", ""},
	{ "........3.9.1.674.7.43..69.5...12..4.........4..86...7.43..18.2.679.8.3.8........", "", "", ""}, // 11723
#endif
	{ "...63...55.4...9..8..4.....12..5.3..3.8.6.7.1..6.1..29.....9..4..3...2.72...71...", "", "", ""}, // 34
#if 0
	{ "...4....339.1.674.7.43.569.5..712..4.7.5.....4..86...79436.18.22679.8.3.8512.....", "", "", ""}, // 1866
#endif

    };
    for(auto test : vtests){
	board<sz> *b=new board<sz>(test.tst);
	b->print();
	b->brute_force_solution(1);
	if(b->is_solved()){
	    std::cout << "Valid solved puzzle\n";
	    std::cout << "Backed up " << b->get_backed_count() << " times\n";
	}else{
	    std::cout << "Valid but not solved puzzle\n";
	}
	b->print();
	std::cout << "count: " << b->count() << '\n';
	std::cout << std::endl;
	delete b;
    }
    return 0;
}
