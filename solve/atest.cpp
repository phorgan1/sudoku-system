#include <iostream>
#include <iomanip>
#include "sudoku.h"
void
print_counts(board<9> &b)
{
    std::cout << "counts:\n";
    std::cout << std::setw(16) << "naked single: " << std::setw(3) << b.get_strategy_count("naked single") << '\n';
    std::cout << std::setw(16) << "hidden single: " << std::setw(3) << b.get_strategy_count("hidden single") << '\n';
    std::cout << std::setw(16) << "intersection: " << std::setw(3) << b.get_strategy_count("intersection") << '\n';
    std::cout << std::setw(16) << "naked double: " << std::setw(3) << b.get_strategy_count("naked double") << '\n';
    std::cout << std::setw(16) << "hidden double: " << std::setw(3) << b.get_strategy_count("hidden double") << '\n';
    std::cout << std::setw(16) << "naked triple: " << std::setw(3) << b.get_strategy_count("naked triple") << '\n';
    std::cout << std::setw(16) << "hidden triple: " << std::setw(3) << b.get_strategy_count("hidden triple") << '\n';
    std::cout << std::setw(16) << "naked quad: " << std::setw(3) << b.get_strategy_count("naked quad") << '\n';
    std::cout << std::setw(16) << "hidden quad: " << std::setw(3) << b.get_strategy_count("hidden quad") << '\n';
    std::cout << std::setw(16) << "x-wing: " << std::setw(3) << b.get_strategy_count("x-wing") << '\n';
    std::cout << std::setw(16) << "swordfish: " << std::setw(3) << b.get_strategy_count("swordfish") << '\n';
    std::cout << std::setw(16) << "jellyfish: " << std::setw(3) << b.get_strategy_count("jellyfish") << '\n';
    std::cout << std::setw(16) << "y-wing: " << std::setw(3) << b.get_strategy_count("y-wing") << '\n';
}
int
main()
{
    /*
    board<9> b( "000" "079" "065"
		"000" "003" "002"
		"005" "060" "093"

		"340" "050" "106"
		"000" "000" "000"
		"608" "020" "059"

		"950" "010" "600"
		"700" "600" "000"
		"820" "390" "000");
    board<9> b( ".......12....35......6...7.7.....3.....4..8..1...........12.....8.....4..5....6..");
    board<9> b( ".36..71..5...........235.7.38..2..6....3.9....1..5..43.7.918...........7..14..29.");
    board<9> b("9..3.8...6..27.....1......7..1....39..29.58..89....4..3......1.....32..4...5.4..2");
		*/
    //board<9> b(".248........41.8.5.8..93..2.4....9....9635.2.1.....57.....4..6..6.1....72....7.9.");
    // given to the guy
    //board<9> b("400801003080020050009000800100050004020974060500010002002000500040080010900602008");
    //board<9> b(".51..9.2.....2.5..4..5...7.8.976......5...6......953.8.4...6..5..3.4.....9.1..24.");
    //board<9> b("1..4....339.1.674.7.43.569.5..712..4.7.5.....4..86...79436.18.22679.8.3.8512.....");
    //board<9> b("1.8..2...4.58.9....32.7.9..52.73.................25.67..3.8.69....6.78.....9..4..");
      board<9> b("71..235......47...6.4..5.2926.......4.......1.......4654.1..8.2...59......847..15");

    b.print_large();
    b.heuristic_solution();
    //b.brute_force_solution();
    b.print_large();
    b.print();
    print_counts(b);
}
