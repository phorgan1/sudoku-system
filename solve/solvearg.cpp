#include <iostream>
#include <iomanip>
#include "sudoku.h"

int
main(int argc, char** argv)
{
    std::string in;
    std::cout << "argc: " << argc << '\n';
    if(argc==1){
	std::cerr << "usage: solvearg BOARDSPEC\n"
	    " Where BOARDSPEC might be something like:\n"
	    ".......12....35......6...7.7.....3.....4..8..1...........12.....8.....4..5....6..\n"
	    " where . signifies an unknown cell and a number signifies a known value\n"
	    " first 9 are values for first row, second 9 second row, etc.\n"
	    " if it's easier you can insert spaces like ... ... .12 ... .35 etc.\n"
	    " or .......12 ....35... ...6...7. etc.\n";


	exit(1);
    }
    if(argc==2){
	in=argv[1];
    }else{
	for(size_t s=1;s<static_cast<size_t>(argc);s++){
	    in+=argv[s];
	}
    }
    try{
	board<9> b(in);
	b.print_large();
	b.heuristic_solution();
	//b.brute_force_solution();
	b.print_large();
	b.print();
	b.print_counts();
    }catch(board<9>::board_shortstring){
	std::cerr << "String too short\n";
	exit(1);
    }catch(board<9>::board_longstring){
	std::cerr << "String too long\n";
	exit(1);
    }

}
