#include <iostream>
#include <sudoku.h>

const size_t sz=9;

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
    // dig_puzzle generates and digs
    //b.dig_puzzle(board<sz>::symtype(board<sz>::ST_HORIZ|board<sz>::ST_VERT),32);
    for(size_t ctr=0;ctr<2;ctr++){
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_NONE),30);
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_HV|board<sz>::ST_MADIAG),30,true);
	b.dig_puzzle(board<sz>::ST_HV,27,true);
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_MDIAG|board<sz>::ST_ADIAG),31);
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_ROT),30);
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_HORIZ|board<sz>::ST_VERT),29);
	//b.dig_puzzle(board<sz>::symtype(board<sz>::ST_HORIZ|board<sz>::ST_VERT|board<sz>::ST_ROT),33);
	b.print();
	size_t num_clues=b.count();
	c=b;
	b.heuristic_solution();
	//std::cerr << static_cast<std::string>(b) << '\n';;
	if(!b.is_solved()){
	    std::cout << num_clues << " clues, ";
	    std::cerr << "had to use brute force to solve it\n";
	    b.brute_force_solution(1);
	    std::cerr << static_cast<std::string>(c) << '\n';
	}else{
	    std::cout << num_clues << " clues, ";
	    b.print_counts();
	    std::cerr << static_cast<std::string>(c) << '\n';
	}
	b.print();
    }
    return 0;
}
