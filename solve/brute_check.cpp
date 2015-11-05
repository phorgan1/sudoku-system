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
    const std::vector<struct test> vtests={
	{ "....0...55.4...9..8..4.....12..5.3..3.8.6.7.1..6.1..29.....9..4..3...2.72...71...", "", "", ""},
	//{ "...63...55.4...9..8..4.....12..5.3..3.8.6.7.1..6.1..29.....9..4..3...2.72...71...", "", "", ""},
	//{ "....1...349.......7.1624...16....54.3.9...2.1.87....96...1739.2.......352...5....", "1 star", "", "Knight Features"},
	//{ "....1....49.......7...24...1......4...9...2.1..7....96...17...2........52...5....", "1 star", "", "Knight Features"},
//	{ "...8.1.........43.5............7.8........1...2..3....6......75..34........2..6..", "", "", ""},
//	{ "5.......9.2.1...7...8...3...4.......................1.3.....8...6...4.2...9.....5", "", "", ""},

    };
    for(auto atest: vtests){
	board<sz> *b=new board<sz>(atest.tst);
	b->print();
	size_t solutions=b->brute_force_solution(-1);
	switch(solutions){
	    case 0:
		std::cout << "no solution\n";
		break;
	    case 1:
		std::cout << "1 solution\n";
		b->brute_force_solution(1);
		b->print();
		break;
	    default:
		std::cout << solutions << " solutions\n";
	}
	if(b->is_solved()){
	    std::cout << "Valid solved puzzle\n";
	}
	delete b;
    }
    return( 0);
}
