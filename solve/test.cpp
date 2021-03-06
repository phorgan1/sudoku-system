#include <iostream>
#define SUDOKU_TESTING
#include <sudoku.h>

const size_t sz=9;

int
main()
{
    //size_t passcount=0,failcount=0;
    std::cout << "running tests: \n";
    std::cout << std::setw(47) << "naked single (1 in row 0, col 0)....";
    std::vector<square> sqs1={
	square(0,0,std::vector<unsigned int>({1})),
    };
    board<9> b1(sqs1);
    b1.heuristic_solution(true);
    if(b1.get_strategy_count("naked single")!=1){
	std::cerr << "failed: expected naked single count of 1\n";
	b1.print_large();
	b1.print_counts();
	return 1;
    }
    if(b1.get_val(0,0)!=1){
	std::cerr << "failed: expected row 0, col 0, set to value 1\n";
	b1.print_large();
	b1.print_counts();
	return 1;
    }
    for(size_t ctr=1;ctr<9;ctr++){
	if(  !b1.check_pval_set(0,ctr,{2,3,4,5,6,7,8,9})
	   ||!b1.check_pval_set(ctr,0,{2,3,4,5,6,7,8,9})){
	    std::cerr << "found our '1' naked single, but the 1 didn't get pulled out of the pvals of all the other cells in row 0 and column 0\n";
	    b1.print_large();
	    return 1;
	}
    }
    for(size_t row=1;row<2;row++){
	for(size_t col=1;col<2;col++){
	    if(  !b1.check_pval_set(row,col,{2,3,4,5,6,7,8,9})){
		std::cerr << "found our '1' naked single, but the 1 didn't get pulled out of the pvals of all the other cells in to top left block\n";
		b1.print_large();
		return 1;
	    }
	}
    }
    for(size_t row=1;row<8;row++){
	for(size_t col=3;col<8;col++){
	    if(  !b1.check_pval_set(row,col,{1,2,3,4,5,6,7,8,9})){
		std::cerr << "found our '1' naked single, but the cells outside block 0, row 0, and column 0 got their pvals messed with\n"; 
		b1.print_large();
		return 1;
	    }
	}
    }
    for(size_t row=3;row<8;row++){
	for(size_t col=1;col<3;col++){
	    if(  !b1.check_pval_set(row,col,{1,2,3,4,5,6,7,8,9})){
		std::cerr << "found our '1' naked single, but the cells outside block 0, row 0, and column 0 got their pvals messed with\n"; 
		b1.print_large();
		return 1;
	    }
	}
    }

    std::cout << "passed\n";
    std::cout << std::setw(47) << "row hidden single (3 in row 0 column 8)....";
    board<9> b2 {
	square(0,0,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(0,1,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(0,2,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(0,3,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(0,4,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(0,5,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(0,6,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(0,7,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(0,8,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
    };
    b2.heuristic_solution(true);
    if(b2.get_strategy_count("hidden single")!=1){
	std::cerr << "failed: expected hidden single count of 1\n";
	b2.print_large();
	b2.print_counts();
	return 1;
    }
    if(b2.get_val(0,8)!=3){
	std::cerr << "failed: expected row 0, col 8, set to value 3\n";
	b2.print_large();
	b2.print_counts();
	return 1;
    }
    std::cout << "passed\n";
    std::cout << std::setw(47) << "column hidden single....";
    board<9> b3 {
	square(0,4,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(1,4,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(2,4,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(3,4,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(4,4,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(5,4,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(6,4,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(7,4,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(8,4,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
    };
    b3.heuristic_solution(true);
    if(b3.get_strategy_count("hidden single")!=1){
	std::cerr << "failed: expected hidden single count of 1\n";
	b3.print_large();
	b3.print_counts();
	return 1;
    }
    std::cout << "passed\n";
    std::cout << std::setw(47) << "block hidden single....";
    board<9> b4 {
	square(0,0,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(0,1,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(0,2,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(1,0,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(1,1,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(1,2,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(2,0,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(2,1,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
	square(2,2,std::vector<unsigned int>({1,2,4,5,6,7,8,9})),
    };
    b4.heuristic_solution(true);
    if(b4.get_strategy_count("hidden single")!=1){
	std::cerr << "failed: expected hidden single count of 1\n";
	b4.print_large();
	b4.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "row naked double....";
    board<9> b5 {
	square(0,0,std::vector<unsigned int>({1,2})),
	square(0,2,std::vector<unsigned int>({1,2})),
    };
    b5.heuristic_solution(true);
    if(b5.get_strategy_count("naked double")!=1){
	std::cout << "failed: expected naked double count of 1\n";
	b5.print_large();
	b5.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "column naked double....";
    board<9> b6 {
	square(4,2,std::vector<unsigned int>({1,2})),
	square(8,2,std::vector<unsigned int>({1,2})),
    };
    b6.heuristic_solution(true);
    if(b6.get_strategy_count("naked double")!=1){
	std::cout << "failed: expected naked double count of 1\n";
	b6.print_large();
	b6.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "block naked double....";
    board<9> b7 {
	square(4,2,std::vector<unsigned int>({1,2})),
	square(5,1,std::vector<unsigned int>({1,2})),
    };
    b7.heuristic_solution(true);
    if(b7.get_strategy_count("naked double")!=1){
	std::cout << "failed: expected naked double count of 1\n";
	b7.print_large();
	b7.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "row hidden double....";
    board<9> b8 {
	square(3,0,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(3,1,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(3,2,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(3,3,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(3,4,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(3,5,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(3,6,std::vector<unsigned int>({1,2,3,4,5,9})),
	square(3,7,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(3,8,std::vector<unsigned int>({1,2,5,6,7,8,9}))
    };
    b8.heuristic_solution(true);
    if(b8.get_strategy_count("hidden double")!=1){
	std::cout << "failed: expected hidden double count of 1\n";
	b8.print_large();
	b8.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "column hidden double....";
    board<9> b9 {
	square(0,8,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(1,8,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(2,8,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(3,8,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(4,8,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(5,8,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(6,8,std::vector<unsigned int>({1,2,3,4,5,9})),
	square(7,8,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(8,8,std::vector<unsigned int>({1,2,5,6,7,8,9}))
    };
    b9.heuristic_solution(true);
    if(b9.get_strategy_count("hidden double")!=1){
	std::cout << "failed: expected hidden double count of 1\n";
	b9.print_large();
	b9.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "block hidden double....";
    board<9> b10 {
	square(6,6,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(6,7,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(6,8,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(7,6,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(7,7,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(7,8,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(8,6,std::vector<unsigned int>({1,2,3,4,5,9})),
	square(8,7,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(8,8,std::vector<unsigned int>({1,2,5,6,7,8,9}))
    };
    b10.heuristic_solution(true);
    if(b10.get_strategy_count("hidden double")!=1){
	std::cout << "failed: expected hidden double count of 1\n";
	b10.print_large();
	b10.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "block/column hidden double....";
    board<9> b11 {
	square(6,6,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(6,7,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(6,8,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(7,6,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(7,7,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(7,8,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(8,6,std::vector<unsigned int>({1,2,5,6,7,8,9})),
	square(8,7,std::vector<unsigned int>({1,2,3,4,5,9})),
	square(8,8,std::vector<unsigned int>({1,2,5,6,7,8,9}))
    };
    b11.heuristic_solution(true);
    if(b11.get_strategy_count("hidden double")!=1){
	std::cout << "failed: expected hidden double count of 1\n";
	b11.print_large();
	b11.print_counts();
	return 1;
    }
    std::cout << "passed\n";
    std::cout << std::setw(47) << "row naked triple....";
    board<9> b12 {
	square(0,0,std::vector<unsigned int>({3,4})),
	square(0,1,std::vector<unsigned int>({4,9})),
	square(0,7,std::vector<unsigned int>({3,9})),
    };
    b12.heuristic_solution(true);
    if(b12.get_strategy_count("naked triple")!=1){
	std::cout << "failed: expected naked triple count of 1\n";
	b12.print_large();
	b12.print_counts();
	return 1;
    }
    std::cout << "passed\n";
    std::cout << std::setw(47) << "column naked triple....";
    board<9> b13 {
	square(1,8,std::vector<unsigned int>({3,4})),
	square(4,8,std::vector<unsigned int>({4,9})),
	square(7,8,std::vector<unsigned int>({3,9})),
    };
    b13.heuristic_solution(true);
    if(b13.get_strategy_count("naked triple")!=1){
	std::cout << "failed: expected naked triple count of 1\n";
	b13.print_large();
	b13.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "block naked triple....";
    board<9> b14 {
	square(0,6,std::vector<unsigned int>({3,4})),
	square(1,7,std::vector<unsigned int>({4,9})),
	square(2,8,std::vector<unsigned int>({3,9})),
    };
    b14.heuristic_solution(true);
    if(b14.get_strategy_count("naked triple")!=1){
	std::cout << "failed: expected naked triple count of 1\n";
	b14.print_large();
	b14.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "block/row naked triple....";
    board<9> b15 {
	square(0,6,std::vector<unsigned int>({3,4})),
	square(0,7,std::vector<unsigned int>({4,9})),
	square(0,8,std::vector<unsigned int>({3,9})),
    };
    b15.heuristic_solution(true);
    if(b15.get_strategy_count("naked triple")!=1){
	std::cout << "failed: expected naked triple count of 1\n";
	b15.print_large();
	b15.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "row hidden triple....";
    board<9> b16 {
	square(0,0,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,1,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,2,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,3,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,4,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,5,std::vector<unsigned int>({3,4,8,9})),
	square(0,6,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,7,std::vector<unsigned int>({4,9})),
	square(0,8,std::vector<unsigned int>({3,9})),
    };
    b16.heuristic_solution(true);
    if(b16.get_strategy_count("hidden triple")!=1){
	std::cout << "failed: expected hidden triple count of 1\n";
	b16.print_large();
	b16.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "column hidden triple....";
    board<9> b17 {
	square(0,8,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(1,8,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(2,8,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(3,8,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(4,8,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(6,8,std::vector<unsigned int>({1,2,5,6,7,8})),
    };
    b17.heuristic_solution(true);
    if(b17.get_strategy_count("hidden triple")!=1){
	std::cout << "failed: expected hidden triple count of 1\n";
	b17.print_large();
	b17.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "block hidden triple....";
    board<9> b18 {
	square(1,0,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(1,1,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(2,2,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,0,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,1,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,2,std::vector<unsigned int>({1,2,5,6,7,8})),
    };
    b18.heuristic_solution(true);
    if(b18.get_strategy_count("hidden triple")!=1){
	std::cout << "failed: expected hidden triple count of 1\n";
	b18.print_large();
	b18.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "block/row hidden triple....";
    board<9> b19 {
	square(1,0,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(1,1,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(1,2,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,0,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,1,std::vector<unsigned int>({1,2,5,6,7,8})),
	square(0,2,std::vector<unsigned int>({1,2,5,6,7,8})),
    };
    b19.heuristic_solution(true);
    if(b19.get_strategy_count("hidden triple")!=1){
	std::cout << "failed: expected hidden triple count of 1\n";
	b19.print_large();
	b19.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "row naked quad....";
    board<9> b20 {
	square(0,0,std::vector<unsigned int>({3,4,7})),
	square(0,6,std::vector<unsigned int>({3,4})),
	square(0,7,std::vector<unsigned int>({4,7,9})),
	square(0,8,std::vector<unsigned int>({3,9})),
    };
    b20.heuristic_solution(true);
    if(b20.get_strategy_count("naked quad")!=1){
	std::cout << "failed: expected naked quad count of 1\n";
	b20.print_large();
	b20.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "column naked quad....";
    board<9> b21 {
	square(0,0,std::vector<unsigned int>({3,4,7})),
	square(3,0,std::vector<unsigned int>({3,4})),
	square(5,0,std::vector<unsigned int>({4,7,9})),
	square(7,0,std::vector<unsigned int>({3,9})),
    };
    b21.heuristic_solution(true);
    if(b21.get_strategy_count("naked quad")!=1){
	std::cout << "failed: expected naked quad count of 1\n";
	b21.print_large();
	b21.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "block naked quad....";
    board<9> b22 {
	square(3,3,std::vector<unsigned int>({3,4,7})),
	square(3,4,std::vector<unsigned int>({3,4})),
	square(4,3,std::vector<unsigned int>({4,7,9})),
	square(5,5,std::vector<unsigned int>({3,9})),
    };
    b22.heuristic_solution(true);
    if(b22.get_strategy_count("naked quad")!=1){
	std::cout << "failed: expected naked quad count of 1\n";
	b22.print_large();
	b22.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "row hidden quad....";
    board<9> b23 {
	square(0,3,std::vector<unsigned int>({2,3,5,6})),
	square(0,4,std::vector<unsigned int>({2,3,5,6})),
	square(0,5,std::vector<unsigned int>({2,3,5,6})),
	square(0,6,std::vector<unsigned int>({2,3,5,6})),
	square(0,8,std::vector<unsigned int>({2,3,5,6})),
    };
    b23.heuristic_solution(true);
    if(b23.get_strategy_count("hidden quad")!=1){
	std::cout << "failed: expected hidden quad count of 1\n";
	b23.print_large();
	b23.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "row x-wing....";
    board<9> b24 {
	square(0,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,2,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(0,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,5,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,6,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(0,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,8,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,2,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(6,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,5,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,6,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(6,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,8,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
    };
    b24.heuristic_solution(true);
    if(b24.get_strategy_count("x-wing")!=1){
	std::cout << "failed: expected x-wing count of 1\n";
	b24.print_large();
	b24.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "column x-wing....";
    board<9> b25 {
	square(0,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(2,4,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(3,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(4,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(5,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,4,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(7,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(2,7,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(3,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(4,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(5,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,7,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(7,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
    };
    b25.heuristic_solution(true);
    if(b25.get_strategy_count("x-wing")!=1){
	std::cout << "failed: expected x-wing count of 1\n";
	b25.print_large();
	b25.print_counts();
	return 1;
    }
    std::cout << "passed\n";
    std::cout << std::setw(47) << "y-wing....";
    board<9> b35 {
	square(0,4,std::vector<unsigned int>({1,5})),
	square(1,3,std::vector<unsigned int>({3,5})),
	square(1,0,std::vector<unsigned int>({1,3})),
    };
    b35.heuristic_solution(true);
    if(b35.get_strategy_count("y-wing")!=1){
	std::cout << "failed: expected y-wing count of 1\n";
	b35.print_large();
	b35.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "row swordfish....";
    board<9> b36 {
	square(0,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,2,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(0,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,5,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(0,6,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,8,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),

	square(3,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,2,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(3,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,5,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(3,6,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,8,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),

	square(6,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,2,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(6,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,5,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(6,6,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,8,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
    };
    b36.heuristic_solution(true);
    if(b36.get_strategy_count("swordfish")!=1){
	std::cout << "failed: expected swordfish count of 1\n";
	b36.print_large();
	b36.print_counts();
	return 1;
    }
    std::cout << "passed\n";


    std::cout << std::setw(47) << "column swordfish....";
    board<9> b37 {
	square(0,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(2,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(4,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(5,0,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(6,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(7,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,0,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),

	square(0,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(2,3,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(3,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(4,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(5,3,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(6,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(7,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,3,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),

	square(0,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(2,7,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(3,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(4,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(5,7,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(6,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(7,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,7,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
    };
    b37.heuristic_solution(true);
    if(b37.get_strategy_count("swordfish")!=1){
	std::cout << "failed: expected swordfish count of 1\n";
	b37.print_large();
	b37.print_counts();
	return 1;
    }
    for(size_t col=0;col<9;col++){
	switch(col){
	    case 1:
	    case 2:
	    case 4:
	    case 5:
	    case 6:
	    case 8:
		if(   !b37.check_pval_set(0,col,{1,2,3,4,5,6,7,8,9})
		   || !b37.check_pval_set(1,col,{1,2,3,4,5,6,7,8,9})
	 	   || !b37.check_pval_set(2,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(3,col,{1,2,3,4,5,6,7,8,9})
		   || !b37.check_pval_set(4,col,{1,2,3,4,5,6,7,8,9})
		   || !b37.check_pval_set(5,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(6,col,{1,2,3,4,5,6,7,8,9})
		   || !b37.check_pval_set(7,col,{1,2,3,4,5,6,7,8,9})
		   || !b37.check_pval_set(8,col,{1,2,3,5,6,7,8,9})) {
		    std::cout << "failed: swordfish found, but target val, (4), not properly cleared out of columns 1,2,4,5,6, and 8 of rows 2, 5, and 8\n";
		    b37.print_large();
		    b37.print_counts();
		}
		break;
	    case 0:
		if(   !b37.check_pval_set(0,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(1,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(2,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(3,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(4,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(5,col,{1,2,3,4,5,6,7,8,9})
		   || !b37.check_pval_set(6,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(7,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(8,col,{1,2,3,4,5,6,7,8,9})) {
		    std::cout << "failed: swordfish found, something happened in column 0 which is supposed to have 4 only in rows 5, and 8\n";
		    b37.print_large();
		    b37.print_counts();
		}
		break;
	    case 3:
	    case 7:
		if(   !b37.check_pval_set(0,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(1,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(2,col,{1,2,3,4,5,6,7,8,9})
		   || !b37.check_pval_set(3,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(4,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(5,col,{1,2,3,4,5,6,7,8,9})
		   || !b37.check_pval_set(6,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(7,col,{1,2,3,5,6,7,8,9})
		   || !b37.check_pval_set(8,col,{1,2,3,4,5,6,7,8,9})) {
		    std::cout << "failed: swordfish found, something happened in columns 3 and 7 which are supposed to have 4 only in rows 2, 5, and 8\n";
		    b37.print_large();
		    b37.print_counts();
		}
		break;
	    default:
		break;
	}
    }

    std::cout << "passed\n";

    std::cout << std::setw(47) << "row jellyfish....";
    board<9> b38 {
	square(0,0,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(0,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,2,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,5,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(0,6,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,8,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),

	square(3,0,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(3,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,2,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(3,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,5,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(3,6,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,8,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),

	square(6,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,2,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(6,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,5,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,6,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,8,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),

	square(8,0,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(8,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,2,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(8,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,5,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(8,6,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,7,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,8,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
    };
    b38.heuristic_solution(true);
    if(b38.get_strategy_count("jellyfish")!=1){
	std::cout << "failed: expected jellyfish count of 1\n";
	b38.print_large();
	b38.print_counts();
	return 1;
    }
    std::cout << "passed\n";
    std::cout << std::setw(47) << "row block intersection....";
    board<9> b26 {
	square(8,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,2,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,3,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,5,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(8,6,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(8,7,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(8,8,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
    };
    b26.heuristic_solution(true);
    if(b26.get_strategy_count("intersection")!=1){
	std::cout << "failed: expected intersection count of 1\n";
	b26.print_large();
	b26.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "column block intersection....";
    board<9> b27 {
	square(0,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(2,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(3,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(4,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(5,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(6,4,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(7,4,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(8,4,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
    };
    b27.heuristic_solution(true);
    if(b27.get_strategy_count("intersection")!=1){
	std::cout << "failed: expected intersection count of 1\n";
	b27.print_large();
	b27.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "block row intersection....";
    board<9> b28 {
	square(0,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,2,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,2,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(2,0,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(2,1,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(2,2,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
    };
    b28.heuristic_solution(true);
    if(b28.get_strategy_count("intersection")!=1){
	std::cout << "failed: expected intersection count of 1\n";
	b28.print_large();
	b28.print_counts();
	return 1;
    }
    std::cout << "passed\n";

    std::cout << std::setw(47) << "block column intersection....";
    board<9> b29 {
	square(0,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(2,0,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(1,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(2,1,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
	square(0,2,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(1,2,std::vector<unsigned int>({1,2,3,4,5,6,7,8,9})),
	square(2,2,std::vector<unsigned int>({1,2,3,5,6,7,8,9})),
    };
    b29.heuristic_solution(true);
    if(b29.get_strategy_count("intersection")!=1){
	std::cout << "failed: expected intersection count of 1\n";
	b29.print_large();
	b29.print_counts();
	return 1;
    }
    std::cout << "passed\n";
    std::cout << std::setw(47) << "xy-chain....";
    board<9> b30 {
	// expect chain:
	// r7r0{|1|,5} -> r0c0{1,|7|} -> r2c2{|3|,7|| -> r2c7{3,|4|}
	//             -> r0c8{|2|,4} -> r7c8{|1|,2}
	// singce r7r0 and r7c8 both claim 1 and can see each other, then
	// we know the initial assertion that r7r0 was 1 is false and can
	// clear that pval from r7r0. That leaves only the 5 so then a
	// naked single will set the 5. That is all that happens.
	square(0,0,std::vector<unsigned int>({1,7})),
	square(0,8,std::vector<unsigned int>({2,4})),
	square(2,2,std::vector<unsigned int>({3,7})),
	square(2,7,std::vector<unsigned int>({3,4})),
	square(7,0,std::vector<unsigned int>({1,5})),
	square(7,8,std::vector<unsigned int>({2,1}))
    };
    b30.heuristic_solution(true);
    if(b30.get_strategy_count("xy-chain")!=1){
	std::cout << "failed: expected xy-chain count of 1\n";
	b30.print_large();
	b30.print_counts();
	return 1;
    }else if(b30.get_val(7,0)!=5){
	std::cout << "failed: expected b[7][0] to have value 51\n";
	b30.print_large();
	b30.print_counts();
	return 1;
    }else if(b30.get_strategy_count("naked single")!=1){
	std::cout << "failed: expected naked single count of 1\n";
	b30.print_large();
	b30.print_counts();
	return 1;
    }

    std::cout << "passed\n";
    std::cout << std::setw(47) << "brute_force_check....";
/*
        +---+---+---+---+---+---+---+---+---+
	|***|***|***|***|***|***|***|***|***|
	|*4*|*8*|*7*|*6*|*5*|*2*|*3*|*9*|*1*|
	|***|***|***|***|***|***|***|***|***|
	+---+---+---+---+---+---+---+---+---+
	|***|***|***|***|***|***|   |   |***|
	|*9*|*5*|*2*|*3*|*4*|*1*|   |   |*6*|
	|***|***|***|***|***|***|78 |78 |***|
	+---+---+---+---+---+---+---+---+---+
	|***|***|***|***|***|***|***|***|***|
	|*3*|*1*|*6*|*9*|*7*|*8*|*4*|*5*|*2*|
	|***|***|***|***|***|***|***|***|***|
	+---+---+---+---+---+---+---+---+---+
	|***|***|***|***|***|***|***|***|***|
	|*8*|*2*|*5*|*7*|*3*|*4*|*6*|*1*|*9*|
	|***|***|***|***|***|***|***|***|***|
	+---+---+---+---+---+---+---+---+---+
	|***|***|***|***|***|***|   |   |***|
	|*1*|*3*|*4*|*2*|*6*|*9*|   |   |*5*|
	|***|***|***|***|***|***|78 |78 |***|
	+---+---+---+---+---+---+---+---+---+
	|***|***|***|***|***|***|***|***|***|
	|*6*|*7*|*9*|*8*|*1*|*5*|*2*|*3*|*4*|
	|***|***|***|***|***|***|***|***|***|
	+---+---+---+---+---+---+---+---+---+
	|***|***|***|***|***|***|***|***|***|
	|*2*|*4*|*3*|*1*|*9*|*7*|*5*|*6*|*8*|
	|***|***|***|***|***|***|***|***|***|
	+---+---+---+---+---+---+---+---+---+
	|***|***|***|***|***|***|***|***|***|
	|*7*|*9*|*8*|*5*|*2*|*6*|*1*|*4*|*3*|
	|***|***|***|***|***|***|***|***|***|
	+---+---+---+---+---+---+---+---+---+
	|***|***|***|***|***|***|***|***|***|
	|*5*|*6*|*1*|*4*|*8*|*3*|*9*|*2*|*7*|
	|***|***|***|***|***|***|***|***|***|
	+---+---+---+---+---+---+---+---+---+
*/
    board<9> b40(
	"487" "652" "391"
	"952" "341" "..6"
	"316" "978" "452"

	"825" "734" "619"
	"134" "269" "..5"
	"679" "815" "234"

	"243" "197" "568"
	"798" "526" "143"
	"561" "483" "927"
    );
    size_t numsols=b40.brute_force_solution(2);
    if(numsols!=2){
	b40.print_large();
	std::cerr << "failed, expected 2 solutions, found: " << numsols << '\n';
	return 1;
    }
    std::cout << "passed\n";
    return 0;
}
