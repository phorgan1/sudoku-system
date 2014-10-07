#include <iostream>
#include <sudoku.h>

const size_t sz=9;

void
print_counts(board<sz> &b)
{
    std::cerr << "  counts:\n";
    std::cerr << "   naked single: " << b.get_strategy_count("naked single") << '\n';
    std::cerr << "   hidden single: " << b.get_strategy_count("hidden single") << '\n';
    std::cerr << "   intersection: " << b.get_strategy_count("intersection") << '\n';
    std::cerr << "   naked double: " << b.get_strategy_count("naked double") << '\n';
    std::cerr << "   hidden double: " << b.get_strategy_count("hidden double") << '\n';
    std::cerr << "   naked triple: " << b.get_strategy_count("naked triple") << '\n';
    std::cerr << "   hidden triple: " << b.get_strategy_count("hidden triple") << '\n';
    std::cerr << "   naked quad: " << b.get_strategy_count("naked quad") << '\n';
    std::cerr << "   hidden quad: " << b.get_strategy_count("hidden quad") << '\n';
    std::cerr << "   x-wing: " << b.get_strategy_count("x-wing") << '\n';
    std::cerr << "   swordfish: " << b.get_strategy_count("swordfish") << '\n';
    std::cerr << "   jellyfish: " << b.get_strategy_count("jellyfish") << '\n';
    std::cerr << "   y-wing: " << b.get_strategy_count("y-wing") << '\n';
}

int
main()
{
    board<sz> b,c;
    // symmetry type chooses whether and which cells will be dug out at the
    // same time as a random cell.  In any case the random cell is dug out,
    // symmetry tells us what else will be dug out
    // ST_NONE  - just dig the random cell
    // ST_HORIZ - also dig the cell reflected across the horiz middle, i.e.
    //            when digging R7C3 also dig R7C5
    // ST_VERT  - dig cell reflected around verticle middle
    // ST_HV    - dig all three cells from all combinations of reflecting
    //            around both axes.
    // 012345678
    // 0..*...@..0
    // 1.**...@@.1  * (1,1), (1,2), (0,2)
    // 2.........2  @ (1,6), (1,7), (0,6) (horizontal reflection of *)
    // 3.........3  % (7,1), (7,2), (8,2) (vertical reflection of *)
    // 4.........4  # (7,6), (7,7), (8,6) (vertical reflection of @)
    // 5.........5  
    // 6.........6 
    // 7.%%...##.7
    // 8..%...#..8
    //  012345678

    // ST_ROT    - combination of ST_ROT90, ST_ROT180 and ST_ROT270
    //             n.b. this is just for convenience, you could also combine
    //             them with ors.
    // ST_ROT90  - also dig cell 90 degrees clockwise
    // ST_ROT180 - also dig cell 180 degrees clockwise
    // ST_ROT270 - also dig cell 270 degrees clockwise
    // ST_MDIAG  - also dig cell reflected about main diagonal (top left to
    //             bottom right
    //
    //  012345678
    // 0.........0
    // 1.........1  Here we see the cells (7,3), (8,4), (8,5), (8,6)
    // 2.........2  main reflection gives (3,7), (4,8), (5,8), (6,8),
    // 3.......@.3
    // 4........@4  * - original cells
    // 5........@5  @ - rotated cells
    // 6........@6
    // 7...*.....7
    // 8....***..8
    //  012345678
    // ST_ADIAG - also dig cell reflected about the anti-diagonal
    // ST_MADIAG- dig the three cells resultant from the combinations of
    //            reflections about both diagonals
    //b.dig_puzzle(board<sz>::symtype(board<sz>::ST_HORIZ|board<sz>::ST_VERT),32);
    while(true){
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_NONE),30);
	b.dig_puzzle(board<sz>::symtype(board<sz>::ST_HV|board<sz>::ST_MADIAG),30,true);
//	b.dig_puzzle(board<sz>::ST_HV,30,true);
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_MDIAG|board<sz>::ST_ADIAG),31);
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_ROT),31);
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_HORIZ|board<sz>::ST_VERT),33);
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_HORIZ|board<sz>::ST_VERT|board<sz>::ST_ROT),33);
	size_t num_clues=b.count();
	std::cerr << "dug\n";
	std::cerr << static_cast<std::string>(b) << '\n';;
	b.print_large();
	b.print();
	c=b;
	b.heuristic_solution();
	//std::cerr << static_cast<std::string>(b) << '\n';;
	if(!b.is_solved()){
	    print_counts(b);
	    std::cerr << "had to use brute force to solve it\n";
	    c.brute_force_solution();
	    c.print();
	    std::cerr << "trying again\n";
	}else{
	    b.print();
	    std::cout << num_clues << " clues, ";
	    print_counts(b);
	    break;
	}
    }
    exit(0);
}
