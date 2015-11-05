//#include <iostream>
//#include <iomanip>
#include "sudoku.h"

int
main()
{
    board<9> b( "000" "630" "005"
	        "504" "000" "900"
		"800" "400" "000"
		
		"120" "050" "300"
		"308" "060" "701"
		"006" "010" "029"

		"000" "009" "004"
		"003" "000" "207"
		"200" "071" "000" );
    b.print_large();
    b.heuristic_solution();
    b.print_counts();
    b.print_large();
}

